﻿using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

using System;
using Microsoft.Win32;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows;

using Calculator.Infra.Service;
using Calculator.Infra.Model;
using Calculator.Infra.Event;
using Calculator.Infra.Helper;

namespace Calculator.ViewModels
{
    class CalculatorViewModel : BindableBase
    {

        [DllImport("parser.dll")]
        public static extern IntPtr retString(string str);
        #region System

        private IRepository _repository;
        private IEventAggregator _eventAggregator { get; }

        private bool IsShowTreeViwer;
        private bool _inputEndState;

        private bool _networkState;
        public bool NetworkState
        {
            get { return _networkState; }
            set
            { 
                _networkState = value;
                NetworkStateText = value ? "CONNECTED" : "DISCONNECT";
            }
        }

        private string _networkStateText;
        public string NetworkStateText
        {
            get { return _networkStateText; }
            set { SetProperty(ref _networkStateText, value); }
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
            OpenFileDialog ofdlg = new OpenFileDialog
            {
                InitialDirectory = @"C:\driver",   // 기본 폴더
                CheckFileExists = true,   // 파일 존재여부확인
                CheckPathExists = true   // 폴더 존재여부확인
            };

            // 파일 열기 (값의 유무 확인)
            if (ofdlg.ShowDialog().GetValueOrDefault())
            {
                //파일로 부터 수식을 읽어옴
                string[] expsFromFile = File.ReadAllLines(@ofdlg.FileName);

                //수식 라인별로 수행
                foreach (string exp in expsFromFile)
                {
                    /*
                     * 읽어온 라인 별로 파서를 호출해 파싱
                     * e.g.) strign parsedData = Pasrger.parsingLogic(exp);
                     * 
                     * 생성된 트리 문자열을 서버로 전송
                     * e.g.) string result = Conn.sendData(parsedData);
                     * 
                     * 계산 히스토리에 저장
                     * e.g.) DataModel.history(exp, result);
                     */
                }
            }
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


        private void UpdateNetworkState(bool isConnect)
        {
            NetworkState = isConnect;
        }

        #endregion

        #region 계산기

        private string _value;
        public string Value
        {
            get { return _value; }
            set { SetProperty(ref _value, value); }
        }

        private string _historyValue;
        public string HistoryValue
        {
            get { return _historyValue; }
            set { SetProperty(ref _historyValue, value); }
        }

       
        private DelegateCommand<string> _inputNumberButtonCommand;
        public DelegateCommand<string> InputNumberButtonCommand => _inputNumberButtonCommand ?? (_inputNumberButtonCommand = new DelegateCommand<string>(InputNumberButton));
        public void InputNumberButton(string key)
        {
            if (_inputEndState) ClearView();

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
            if (_inputEndState) ClearView();

            string value = _value;
            string history = _historyValue;
            switch(name)
            {
                case "plus":
                    if (_value.Equals("")) return;
                    history = Number.InputOperator(history, value, '+');
                    value = "";
                    break;

                case "minus":
                    if (_value.Equals("")) return;
                    history = Number.InputOperator(history, value, '-');
                    value = "";
                    break;

                case "multiply":
                    if (_value.Equals("")) return;
                    history = Number.InputOperator(history, value, '*');
                    value = "";
                    break;

                case "division":
                    if (_value.Equals("")) return;
                    history = Number.InputOperator(history, value, '/');
                    value = "";
                    break;

                case "equal":
                    if (!_networkState) return;
                    if (_value.Equals("")) return;
                    history = Number.InputOperator(history, value, '=');
                    value = Calculate(history.Replace("=", ""));
                    _inputEndState = true;
                    break;

                case "reset":
                    value = "";
                    history = "";
                    break;
                case "bs":
                    if (_value.Equals("")) return;

                    value = Number.BackSpace(_value);
                    break;

                case "open":
                    break;
                case "close":
                    break;
                default:
                    break;
            }

            Value = value;
            HistoryValue = history;
        }

        private void ClearView()
        {
            Value = "";
            HistoryValue = "";

            _inputEndState = false;
        }
        #endregion

        #region 계산기 Logic
        private string Calculate(string formula)
        {
            string result = default;
            //Tree 코드 변환
            try
            {
                string TreeValue = "Tree";

                IntPtr ptr = retString(formula);
                string Message = Marshal.PtrToStringAnsi(ptr);
                Marshal.FreeHGlobal(ptr);

                if (Message == null)
                {
                    //잘못된 인자이니 에러출력
                    return "ERROR";
                }

                _repository.Client.Send(Message + System.Environment.NewLine);

                //연산 결과 표시
                result = _repository.Client.Recv();
                if (result != "")
                {
                    //_eventAggregator.GetEvent<SendTreeViewerDataEvent>().Publish();
                    _repository.AddLog(new Log(formula + "=", TreeValue, result));
                }

            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());

            }
            return result;
        }


        #endregion


        public CalculatorViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;

            _eventAggregator.GetEvent<SendNetworkStateEvent>().Subscribe(UpdateNetworkState);
            _eventAggregator.GetEvent<KeyInputNumberEvent>().Subscribe(InputNumberButton);
            _eventAggregator.GetEvent<KeyInputEvent>().Subscribe(InputEventButton);
            Value = "";
            HistoryValue = "";

            IsShowTreeViwer = false;
            _inputEndState = false;
            NetworkState = false;
        }

    }
}
