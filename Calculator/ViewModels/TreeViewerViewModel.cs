using Prism.Mvvm;
using Prism.Commands;
using Prism.Events;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Calculator.Infra.Event;
namespace Calculator.ViewModels
{
    class TreeViewerViewModel : BindableBase
    {
        private IEventAggregator _ea;

        private string _value;
        public string Value
        {
            get { return _value; }
            set { SetProperty(ref _value, value); }
        }

        private void SetTreeViewerValue(string value)
        {
            _value = value;
        }

        public TreeViewerViewModel(IEventAggregator ea)
        {
            _ea = ea;

            _ea.GetEvent<SendTreeViewerDataEvent>().Subscribe(SetTreeViewerValue);
        }

    }
}
