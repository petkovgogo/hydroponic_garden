using System.Net.Mail;
using InfluxDB.Client;
using InfluxDB.Client.Api.Domain;
using InfluxDB.Client.Writes;
using Newtonsoft.Json;

public class DataService
{
    private readonly IHttpClientFactory m_clientFactory;
    const string TOKEN = "HoLZ-O3hgjsvNjA6zKiXu9Erny7hX2e5f_VcDmU-swGDMAWIH-duPgDOzVILLIWNlB8ZCzdH1e_fRDsMyB-v8g==";
    const string BUCKET = "rpi-sensor-data";
    const string ORG = "hydrop-project";

    public DataService(IHttpClientFactory clientFactory)
    {
        m_clientFactory = clientFactory;
    }

    public async Task GetData()
    {
        HttpClient client = m_clientFactory.CreateClient();
        client.BaseAddress = new Uri("http://gmalinka.local/cgi-bin/");

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
        using var client = InfluxDBClientFactory.Create("http://rpi-sensor-data-db", TOKEN);
        using var writeApi = client.GetWriteApi();

        writeApi.WritePoint(BUCKET, ORG, data);
    }
}