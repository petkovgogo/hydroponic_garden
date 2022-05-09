using System.Net.Mail;
using InfluxDB.Client;
using InfluxDB.Client.Api.Domain;
using InfluxDB.Client.Writes;
using Newtonsoft.Json;
using Microsoft.Extensions.Configuration;

public class DataService
{
    private readonly IHttpClientFactory m_clientFactory;
    private readonly string BASE_URI;
    private readonly string TOKEN;
    private readonly string BUCKET;
    private readonly string ORG;

    public DataService(IHttpClientFactory clientFactory, IConfiguration config)
    {
        m_clientFactory = clientFactory;
        BASE_URI = config.GetValue<string>("RPiUri");
        TOKEN = config.GetValue<string>("InfluxDB:Token");
        BUCKET = config.GetValue<string>("InfluxDB:Bucket");
        ORG = config.GetValue<string>("InfluxDB:Org");
    }

    public async Task GetData()
    {
        HttpClient client = m_clientFactory.CreateClient();
        client.BaseAddress = new Uri(BASE_URI);

        await PollBME280(client);
        await PollPH(client);
        await PollTDS(client);
        // await PollLiquidLevel(client);

    }

    private async Task PollBME280(HttpClient client)
    {
        HttpResponseMessage result = await client.GetAsync("cgi-bme280.cgi");

        if (result.IsSuccessStatusCode)
        {
            string content = await result.Content.ReadAsStringAsync();
            BME280Data sensorData = JsonConvert.DeserializeObject<BME280Data>(content);

            SaveData(PointData
                .Measurement("hydroponic_garden")
                .Tag("sensor", "bme280")
                .Field("temperature", sensorData.Temperature)
                .Timestamp(DateTime.UtcNow, WritePrecision.Ns)
            );

            SaveData(PointData
                .Measurement("hydroponic_garden")
                .Tag("sensor", "bme280")
                .Field("humidity", sensorData.Humidity)
                .Timestamp(DateTime.UtcNow, WritePrecision.Ns)
            );

            SaveData(PointData
                .Measurement("hydroponic_garden")
                .Tag("sensor", "bme280")
                .Field("pressure", sensorData.Pressure / 100) // pressure from [Pa] to [hPa]
                .Timestamp(DateTime.UtcNow, WritePrecision.Ns)
            );
        }
    }

    private async Task PollPH(HttpClient client)
    {
        HttpResponseMessage result = await client.GetAsync("cgi-ph.cgi");

        if (result.IsSuccessStatusCode)
        {
            string content = await result.Content.ReadAsStringAsync();
            PHData sensorData = JsonConvert.DeserializeObject<PHData>(content);

            SaveData(PointData
                .Measurement("hydroponic_garden")
                .Tag("sensor", "ph")
                .Field("ph", sensorData.PH)
                .Timestamp(DateTime.UtcNow, WritePrecision.Ns)
            );
        }
    }

    private async Task PollTDS(HttpClient client)
    {
        HttpResponseMessage result = await client.GetAsync("cgi-tds.cgi");

        if (result.IsSuccessStatusCode)
        {
            string content = await result.Content.ReadAsStringAsync();
            TDSData sensorData = JsonConvert.DeserializeObject<TDSData>(content);

            SaveData(PointData
                .Measurement("hydroponic_garden")
                .Tag("sensor", "tds")
                .Field("tds", sensorData.TDS)
                .Timestamp(DateTime.UtcNow, WritePrecision.Ns)
            );
        }
    }

    private async Task PollLiquidLevel(HttpClient client)
    {
        HttpResponseMessage result = await client.GetAsync("cgi-liquid-level.cgi");

        if (result.IsSuccessStatusCode)
        {
            string content = await result.Content.ReadAsStringAsync();
            LiquidLevelData sensorData = JsonConvert.DeserializeObject<LiquidLevelData>(content);


            if (sensorData.State == 1)
            {
                // TODO send warning via email
            }
        }
    }

    private void SaveData(PointData data)
    {
        using var client = InfluxDBClientFactory.Create("http://rpi-sensor-data-db:8086", TOKEN);
        using var writeApi = client.GetWriteApi();

        writeApi.WritePoint(BUCKET, ORG, data);
    }
}
