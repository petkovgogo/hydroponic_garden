using System.ComponentModel.DataAnnotations;

namespace Webapp.Models;

class SensorData
{
    [Display(Name = "Temperature [°C]")]
    public double Temperature { get; init; }

    [Display(Name = "Humidity [%]")]
    public double Humidity { get; init; }

    [Display(Name = "Pressure [hPa]")]
    public double Pressure { get; init; }

    [Display(Name = "Acidity/Basity [pH]")]
    public double PH { get; init; }

    [Display(Name = "TDS [ppm]")]
    public int TDS { get; init; }
}