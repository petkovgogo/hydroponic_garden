namespace Webapp.Models.ViewModels;
using System.ComponentModel.DataAnnotations;

public class PlantVM
{
    public int Id { get; set; }

    [Required]
    [StringLength(100)]
    [Display(Name = "Name")]
    public string Name { get; set; }

    [Display(Name = "Notes")]
    public string? Notes { get; set; }     

    [Required]
    [Display(Name = "Minimum Temperature")]
    [Range(-40, 60)]
    public double? MinTemperature { get; set; }   

    [Required]
    [Display(Name = "Maximum Temperature")]
    [Range(-40, 60)]
    public double? MaxTemperature { get; set; }

    [Required]
    [Display(Name = "Minimum Humidity")]
    [Range(0.1, 100)]
    public double? MinHumidity { get; set; }

    [Required]
    [Display(Name = "Maximum Humidity")]
    [Range(0.1, 100)]
    public double? MaxHumidity { get; set; }

    [Required]
    [Display(Name = "Minimum pH")]
    [Range(1, 14)]
    public double? MinPh { get; set; }

    [Required]
    [Display(Name = "Maximum pH")]
    [Range(1, 14)]
    public double? MaxPh { get; set; }

    [Required]
    [Display(Name = "Minimum TDS")]
    [Range(1, 1300)]
    public int? MinTds { get; set; }     
    
    [Required]
    [Display(Name = "Maximum TDS")]
    [Range(1, 1300)]
    public int? MaxTds { get; set; }   

    [Display(Name = "Planted")]
    public bool IsPlanted { get; set; }

    [Display(Name = "Active")]
    public bool  IsActive { get; set; } = true;
}