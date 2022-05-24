using System;
using System.Threading.Tasks;
using InfluxDB.Client;
using Microsoft.Extensions.Configuration;

namespace Webapp.Services;

public class InfluxDBService
{
    private readonly string _token;

    public InfluxDBService(IConfiguration config)
    {
        _token = config.GetValue<string>("InfluxDB:Token");
    }

    public void Write(Action<WriteApi> action)
    {
        using var client = InfluxDBClientFactory.Create("http://localhost:8086", _token);
        using var write = client.GetWriteApi();
        action(write);
    }

    public async Task<T> QueryAsync<T>(Func<QueryApi, Task<T>> action)
    {
        using var client = InfluxDBClientFactory.Create("http://localhost:8086", _token);
        var query = client.GetQueryApi();
        return await action(query);
    }
}

