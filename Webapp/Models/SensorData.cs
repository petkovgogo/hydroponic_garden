using System.ComponentModel.DataAnnotations;

namespace Webapp.Models;

class SensorData
{
    [Display(Name = "Temperature [°C]")]
    public decimal? Temperature { get; init; }

    [Display(Name = "Humidity [%]")]
    public int? Humidity { get; init; }

    [Display(Name = "Pressure [hPa]")]
    public int? Pressure { get; init; }

    [Display(Name = "Acidity/Basity [pH]")]
    public int? PH { get; init; }

    [Display(Name = "TDS [ppm]")]
    public int? TDS { get; init; }
}