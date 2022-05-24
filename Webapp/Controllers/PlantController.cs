using Microsoft.AspNetCore.Mvc;

namespace Webapp.Controllers;

public class PlantController : Controller
{
    public async Task<IActionResult> Index()
    {
        return View();
    }
}