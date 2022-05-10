using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Webapp.Models;
using Webapp.Services;

namespace Webapp.Controllers;

public class HomeController : Controller
{
    private readonly ILogger<HomeController> _logger;
    private readonly string _bucket;
    private readonly string _org;

    public HomeController(IConfiguration config, ILogger<HomeController> logger)
    {
        _logger = logger;
        _bucket = config.GetValue<string>("InfluxDB:Bucket");
        _org = config.GetValue<string>("InfluxDB:Org");
    }

    public async Task<IActionResult> Index([FromServices] InfluxDBService service)
    {
        var results = await service.QueryAsync(async query =>
        {
            var flux = $"from(bucket:\"{_bucket}\") |> range(start: -1m)";
            var tables = await query.QueryAsync(flux, _org);

            return tables.SelectMany(table =>
                table.Records.Select(record =>
                    new SensorData
                    {
                        Temperature = decimal.Parse(record.GetValue().ToString()),
                        Humidity = int.Parse(record.GetValue().ToString()),
                        Pressure = int.Parse(record.GetValue().ToString()),
                        PH = int.Parse(record.GetValue().ToString()),
                        TDS = int.Parse(record.GetValue().ToString()),
                    }));
        });

        return View(results[0]);
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
}
