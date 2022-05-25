using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Mvc;
using Webapp.Models.ViewModels;
using Webapp.Services;
using Webapp.Models.Data;

namespace Webapp.Controllers;

public class PlantController : Controller
{
    private readonly Repository _repo;

    public PlantController(Repository repo)
    {
        _repo = repo;
    }

    public async Task<IActionResult> Index()
    {
        IEnumerable<PlantListVM> model = await _repo.All<Plant>()
            .Where(p => p.IsActive)
            .Select(p => new PlantListVM()
            {
                Id = p.Id,
                Name = p.Name,
                Temperature = $"{p.MinTemperature} - {p.MaxTemperature} °C",
                Humidity = $"{p.MinHumidity} - {p.MaxHumidity} %",
                PH = $"{p.MinPh} - {p.MaxPh} pH",
                Tds = $"{p.MinTds} - {p.MaxTds} ppm",
                Planted = p.IsPlanted ? "yes" : "no"
            })
            .ToListAsync();

        return View(model);
    }

    [HttpGet]
    public async Task<IActionResult> Add()
    {
        PlantVM model = new PlantVM();
        ViewData["Title"] = "Add new Plant";

        return View("Edit", model);
    }

    [HttpGet]
    public async Task<IActionResult> Edit(int id)
    {
        var model = await _repo.All<Plant>()
            .Where(p => p.Id == id)
            .Select(p => new PlantVM()
            {
                Id = p.Id,
                IsActive = p.IsActive,
                IsPlanted = p.IsPlanted,
                MaxHumidity = p.MaxHumidity,
                MaxPh = p.MaxPh,
                MaxTds = p.MaxTds,
                MaxTemperature = p.MaxTemperature,
                MinHumidity = p.MinHumidity,
                MinPh = p.MinPh,
                MinTds = p.MinTds,
                MinTemperature = p.MinTemperature,
                Name = p.Name,
                Notes = p.Notes
            })
            .FirstOrDefaultAsync();

        return View(model);
    }

    [HttpPost]
    public async Task<IActionResult> Edit(PlantVM model)
    {
        if (!ModelState.IsValid)
        {
            return View(model);
        }

        Plant entity = null;

        if (model.Id == 0)
        {
            entity = new Plant();
        }
        else
        {
            entity = await _repo.GetByIdAsync<Plant>(model.Id);
        }

        entity.IsActive = model.IsActive;
        entity.IsPlanted = model.IsPlanted;
        entity.MaxHumidity = model.MaxHumidity ?? 0;
        entity.MaxPh = model.MaxPh ?? 0;
        entity.MaxTds = model.MaxTds ?? 0;
        entity.MaxTemperature = model.MaxTemperature ?? 0;
        entity.MinHumidity = model.MinHumidity ?? 0;
        entity.MinPh = model.MinPh ?? 0;
        entity.MinTds = model.MinTds ?? 0;
        entity.MinTemperature = model.MinTemperature ?? 0;
        entity.Name = model.Name;
        entity.Notes = model.Notes;

        if (entity.Id == 0)
        {
            await _repo.AddAsync(entity);
        }

        await _repo.SaveChangesAsync();

        return RedirectToAction(nameof(Index));
    }

    public async Task<IActionResult> Delete(int id)
    {
        var entity = await _repo.GetByIdAsync<Plant>(id);

        entity.IsActive = false;

        await _repo.SaveChangesAsync();

        return RedirectToAction(nameof(Index));
    }
}