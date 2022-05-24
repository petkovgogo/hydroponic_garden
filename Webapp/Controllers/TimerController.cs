using Microsoft.AspNetCore.Mvc;

namespace Webapp.Controllers;

public class TimerController : Controller
{
    public async Task<IActionResult> Index()
    {
        return View();
    }
}