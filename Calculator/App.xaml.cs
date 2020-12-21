using Prism.Ioc;
using Prism.Unity;
using System.Windows;
using Calculator.Views;
using Calculator.Infra.Service;

namespace Calculator
{
    public partial class App : PrismApplication
    {
        protected override Window CreateShell()
        {
            return Container.Resolve<CalculatorView>();
        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterSingleton<IRepository, Repository>();
        }
    }
}
