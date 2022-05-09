using System.Timers;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

public class TimedHostedService : IHostedService, IDisposable
{
    private readonly ILogger<TimedHostedService> m_logger;
    private readonly IServiceProvider m_serviceProvider;
    private System.Timers.Timer m_timer = null;
    private bool m_disposedValue;
    private const int PERIOD = 60000; // 60s

    public TimedHostedService(
        ILogger<TimedHostedService> logger,
        IServiceProvider serviceProvider)
    {
        m_logger = logger;
        m_serviceProvider = serviceProvider;
    }

    public Task StartAsync(CancellationToken stoppingToken)
    {
        m_logger.LogInformation("Start Async");

        m_timer = new System.Timers.Timer();
        m_timer.Interval = PERIOD;
        m_timer.Elapsed += TimerElapsed;
        m_timer.Start();

        return Task.CompletedTask;
    }

    private void TimerElapsed(object sender, ElapsedEventArgs e)
    {
        try
        {
            m_timer.Stop();
            m_timer.Interval = PERIOD;

            m_logger.LogInformation("Timer Elapsed");

            using (IServiceScope scope = m_serviceProvider.CreateScope())
            {
                DataService service = scope.ServiceProvider.GetService<DataService>();
                service.GetData().Wait();
            }
        }
        catch (System.Exception ex)
        {
            m_logger.LogError(ex, ex.Message);
        }
        finally
        {
            m_timer.Start();
        }
    }

    public Task StopAsync(CancellationToken stoppingToken)
    {
        m_logger.LogInformation("StopAsync");

        return Task.CompletedTask;
    }

    protected virtual void Dispose(bool disposing)
    {
        if (!m_disposedValue)
        {
            if (disposing)
            {
                m_timer?.Stop();
                m_timer?.Close();
                m_timer?.Dispose();
            }

            m_disposedValue = true;
        }
    }

    public void Dispose()
    {
        // Do not change this code. Put cleanup code in 'Dispose(bool disposing)' method
        Dispose(disposing: true);
        GC.SuppressFinalize(this);
    }
}