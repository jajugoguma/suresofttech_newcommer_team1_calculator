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
using Calculator.Infra.Event;

namespace Calculator.ViewModels
{
    class CalculatorViewModel : BindableBase
    {
        #region System

        private IRepository _repository;
        private IEventAggregator _eventAggregator { get; }

        private bool IsShowTreeViwer;

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
            if(!IsShowTreeViwer)
            {
                IsShowTreeViwer = true;

                Value = "트리 오픈";
                Calculator.Views.TreeViewerView modal = new Calculator.Views.TreeViewerView();
                modal.Show();
            }
        }

        private DelegateCommand importFileCommand;
        public DelegateCommand ImportFileCommand => importFileCommand ?? (importFileCommand = new DelegateCommand(ImportFile));
        private void ImportFile()
        {

        }

        private DelegateCommand closeProgramCommand;
        public DelegateCommand CloseProgramCommand => closeProgramCommand ?? (closeProgramCommand = new DelegateCommand(CloseProgram));
        private void CloseProgram()
        {
            System.Windows.Application.Current.Shutdown();
        }

        private DelegateCommand showNetworkCommand;
        public DelegateCommand ShowNetworkCommand => showNetworkCommand ?? (showNetworkCommand = new DelegateCommand(ShowNetwork));
        private void ShowNetwork()
        {
            Views.NetworkView popup = new Views.NetworkView();
            popup.ShowDialog();
        }

        private DelegateCommand optionCommand;
        public DelegateCommand OptionCommand => optionCommand ?? (optionCommand = new DelegateCommand(Option));
        private void Option()
        {
            Views.SettingView popup = new Views.SettingView();
            popup.ShowDialog();
        }
        #endregion

        #region 계산기

        private string _value;
        public string Value
        {
            get { return _value; }
            set { SetProperty(ref _value, value); }
        }


        private DelegateCommand testCommand;
        public DelegateCommand TestCommand => testCommand ?? (testCommand = new DelegateCommand(Test));
        private void Test()
        {
            _repository.AddLog(new Log("formula", "tree", "result"));
        }

        private void SetValue(string value)
        {
            Value = value;
        }

        #endregion
        

        public CalculatorViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;

            _eventAggregator.GetEvent<EditCalculatorValueEvent>().Subscribe(SetValue);

            Value = "Start Calculator!!";
            IsShowTreeViwer = false;
        }
    }
}
