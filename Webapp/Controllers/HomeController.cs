using System.Diagnostics;
using System.Text;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Configuration;
using Webapp.Models;
using Webapp.Services;
using Newtonsoft.Json;
using InfluxDB.Client.Core.Flux.Domain;

namespace Webapp.Controllers;

public class HomeController : Controller
{
    private readonly ILogger<HomeController> _logger;
    private readonly string _baseUri;
    private readonly string _bucket;
    private readonly string _org;
    private readonly IHttpClientFactory _httpClientFactory;


    private readonly InfluxDBService _influxService;

    public HomeController(
        IConfiguration config,
        ILogger<HomeController> logger,
        InfluxDBService influxService,
        IHttpClientFactory httpClientFactory)
    {
        _logger = logger;
        _baseUri = config.GetValue<string>("RPiUri");
        _bucket = config.GetValue<string>("InfluxDB:Bucket");
        _org = config.GetValue<string>("InfluxDB:Org");
        _influxService = influxService;
        _httpClientFactory = httpClientFactory;
    }

    public async Task<IActionResult> Index()
    {
        var result = await _influxService.QueryAsync(async query =>
        {
            var flux = $"from(bucket:\"{_bucket}\") |> range(start: -15m)";
            var tables = await query.QueryAsync(flux, _org);


            return new SensorData
            {
                Temperature = GetMeasurement(tables, "temperature"),
                Humidity = GetMeasurement(tables, "humidity"),
                Pressure = GetMeasurement(tables, "pressure"),
                PH = GetMeasurement(tables, "ph"),
                TDS = (int)GetMeasurement(tables, "tds")
            };
        });

        return View(result);
    }

    public async Task<IActionResult> GetStatus()
    {
        HttpClient client = _httpClientFactory.CreateClient();
        client.BaseAddress = new Uri(_baseUri);

        HttpResponseMessage result = await client.GetAsync("cgi-relay-response.cgi");
        string content = await result.Content.ReadAsStringAsync();

        if (result.IsSuccessStatusCode)
        {
            return Ok(JsonConvert.DeserializeObject<ElApplianceStats>(content));
        }

        return StatusCode(StatusCodes.Status500InternalServerError);
    }

    public async Task<IActionResult> SetStatus(ElApplianceControl elAppControl)
    {
        HttpClient client = _httpClientFactory.CreateClient();
        client.BaseAddress = new Uri(_baseUri);
        string controlData = $"{elAppControl.Channel}={elAppControl.NewState}";
        StringContent queryString = new StringContent(controlData, Encoding.UTF8, "application/json");

        HttpResponseMessage result = await client.PostAsync("cgi-relay-set.cgi?" + controlData, queryString);
        string content = await result.Content.ReadAsStringAsync();

        if (result.IsSuccessStatusCode)
        {
            return Ok(JsonConvert.DeserializeObject<ElApplianceStats>(content));
        }

        return StatusCode(StatusCodes.Status500InternalServerError);
    }

    public IActionResult Privacy()
    {
        return View();
    }

    [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
    public IActionResult Error()
    {
        return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
    }

    private double GetMeasurement(List<FluxTable> tables, string measurement)
    {
        var measurementTable = tables
                .Where(t => t.Records
                    .Any(r => r.GetValueByKey("_field") as string == measurement))
                .FirstOrDefault();
        double measurementValue = 0D;

        if (measurementTable != null)
        {
            measurementValue = Math.Round(measurementTable.Records
            .Select(r => r.GetValue() as double?)
            .Average() ?? 0D, 2);
        }

        return measurementValue;
    }
}
