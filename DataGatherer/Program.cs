using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Configuration;
using System.IO;

class Program
{
    static async Task Main(string[] args)
    {
        IHost host = new HostBuilder()
            .ConfigureAppConfiguration((hostContext, config) => 
            {
                config.SetBasePath(Directory.GetCurrentDirectory());
                config.AddJsonFile("appsettings.json", true);
                config.AddUserSecrets<DataService>();
            })
            .ConfigureServices(services => 
            {
                services.AddHostedService<TimedHostedService>();
                services.AddHttpClient();
                services.AddScoped<DataService>();
            })
            .ConfigureLogging((hostContext, configureLogging) => 
            {
                configureLogging.AddConsole();
                configureLogging.AddDebug();
                configureLogging.SetMinimumLevel(LogLevel.Debug);
            })
            .Build();
            
        await host.RunAsync();
    }
}
