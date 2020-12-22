using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;

using Calculator.Infra.Service;
using Calculator.Infra.Model;
using Calculator.Infra.Event;
using Calculator.Infra.Helper;

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

       
        private DelegateCommand<string> _inputNumberButtonCommand;
        public DelegateCommand<string> InputNumberButtonCommand => _inputNumberButtonCommand ?? (_inputNumberButtonCommand = new DelegateCommand<string>(InputNumberButton));
        public void InputNumberButton(string key)
        {
            switch (key)
            {
                case "pm":
                    if (_value.Equals(""))
                        return;

                    Value = Number.ChangePlusMinus(_value);
                    break;

                case "dot":
                    return;
                    break;

                //숫자인경우
                default:
                    if (_value.Length >= 15)//자리수
                        return;

                    Value = Number.Add(_value, key);
                    break;
            }
        }
            

        private DelegateCommand<string> _inputEventButtonCommand;
        public DelegateCommand<string> InputEventButtonCommand => _inputEventButtonCommand ?? (_inputEventButtonCommand = new DelegateCommand<string>(InputEventButton));
        public void InputEventButton(string name)
        {
            switch(name)
            {
                case "plus":
                    break;

                case "minus":
                    break;

                case "multiply":
                    break;

                case "division":
                    break;

                case "equal":
                    break;

                case "reset":
                    Value = "";
                    break;
                case "bs":
                    if (_value.Equals(""))
                        return;

                    Value = Number.BackSpace(_value);
                    break;

                case "open":
                    break;
                case "close":
                    break;
                default:
                    break;
            }

        }
        #endregion


        public CalculatorViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;

            _eventAggregator.GetEvent<EditCalculatorValueEvent>().Subscribe(SetValue);

            _eventAggregator.GetEvent<KeyInputNumberEvent>().Subscribe(InputNumberButton);
            _eventAggregator.GetEvent<KeyInputEvent>().Subscribe(InputEventButton);
            Value = "";
            IsShowTreeViwer = false;
        }

    }
}
