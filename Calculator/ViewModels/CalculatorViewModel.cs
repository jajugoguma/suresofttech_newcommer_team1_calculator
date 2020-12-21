using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

using Calculator.Infra.Service;
using Calculator.Infra.Model;

namespace Calculator.ViewModels
{
    class CalculatorViewModel : BindableBase
    {
        #region System

        private IRepository _repository;

        private bool IsShowTreeViwer;



        private IEventAggregator _eventAggregator;
        public IEventAggregator EventAggregator
        {
            get { return _eventAggregator; }
            set { SetProperty(ref _eventAggregator, value); }
        }

        //History View
        private Views.HistoryView hismo = null;
        private DelegateCommand showHistoryCommand;
        public DelegateCommand ShowHistoryCommand => showHistoryCommand ?? (showHistoryCommand = new DelegateCommand(ShowHistory));
        private void ShowHistory()
        {
            if (hismo == null)
            {
                hismo = new Calculator.Views.HistoryView();
                
                hismo.Closed += (x, y) => { hismo = null; };
                hismo.Show();
            }
        }

        //Tree Viewer View
        private DelegateCommand showTreeViwerCommand;
        public DelegateCommand ShowTreeViwerCommand => showTreeViwerCommand ?? (showTreeViwerCommand = new DelegateCommand(ShowTreeViewer));
        private void ShowTreeViewer()
        {
            Value = "트리 오픈";
            Calculator.Views.TreeViewerView modal = new Calculator.Views.TreeViewerView();
            modal.Show();
        }


        private DelegateCommand closeProgramCommand;
        public DelegateCommand CloseProgramCommand => closeProgramCommand ?? (closeProgramCommand = new DelegateCommand(CloseProgram));
        private void CloseProgram()
        {
            System.Windows.Application.Current.Shutdown();
        }


        public CalculatorViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;
            

            Value = "Start Calculator!!";

            IsShowTreeViwer = false;
        }
        #endregion

        #region 계산기

        private string value;
        public string Value
        {
            get { return value; }
            set { SetProperty(ref this.value, value); }
        }

        #endregion
    }
}
