using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace Webapp.Models.Data;

[Table("plants")]
public class Plant
{
    [Key]
    public int Id { get; set; }

    [Required]
    [StringLength(100)]
    public string Name { get; set; }

    [StringLength(1000)]
    public string? Notes { get; set; }     

    public double MinTemperature { get; set; }   

    public double MaxTemperature { get; set; }

    public double MinHumidity { get; set; }

    public double MaxHumidity { get; set; }

    public double MinPh { get; set; }

    public double MaxPh { get; set; }

    public int MinTds { get; set; }     
    
    public int MaxTds { get; set; }   

    public bool IsPlanted { get; set; }

    public bool  IsActive { get; set; } = true;

    public List<PlantNutrient> Nutrients { get; set; }  
}
