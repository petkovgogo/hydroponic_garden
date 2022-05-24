using Microsoft.EntityFrameworkCore;

namespace Webapp.Models.Data;

    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Plant> Plants { get; set; }

        public DbSet<PlantNutrient> Nutrients { get; set; }
    }