using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace Webapp.Models.Data;

[Table("plant_nutrients")]
public class PlantNutrient
{
    [Key]
    public int Id { get; set; }

    public int PlantId { get; set; }

    [Required]
    [StringLength(100)]
    public string Name { get; set; }

    public double Quantity { get; set; }

    [Required]
    [StringLength(20)]
    public string Unit { get; set; }

    [ForeignKey(nameof(PlantId))]
    public Plant Plant { get; set; }
}