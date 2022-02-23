using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

class Program
{
    static async Task Main(string[] args)
    {
        IHost host = new HostBuilder()
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
