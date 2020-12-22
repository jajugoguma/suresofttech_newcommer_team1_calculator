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
#if DEBUG_TEST
            return Container.Resolve<MainWindow>();
#elif DEBUG
            return Container.Resolve<CalculatorView>();
#else
            return Container.Resolve<CalculatorView>();
#endif


        }

        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            containerRegistry.RegisterSingleton<IRepository, Repository>();
        }
    }
}
