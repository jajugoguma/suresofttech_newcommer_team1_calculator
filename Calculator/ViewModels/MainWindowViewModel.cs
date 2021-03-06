﻿
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using Calculator.Infra.Model;
using System.Windows.Data;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using CalendarNetworkClient;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows;
using Microsoft.Win32;

namespace Calculator.ViewModels
{
    class MainWindowViewModel : BindableBase
    {
        public MainWindowViewModel()
        {
            EqualsEnable = false;
            _logs = new ObservableCollection<Log>();
            _client = new Client();
            IP = "127.0.0.1";
            Port = "18000";
        }

        [DllImport("parser.dll")]
        public static extern IntPtr retString(string str);

        #region Network

        public Client _client;

        //네트워크 변수
        private string _ip;
        public string IP { get { return _ip; } set { SetProperty(ref _ip, value); } }

        private string _port;
        public string Port { get { return _port; } set { SetProperty(ref _port, value); } }

        private string _networkState;
        public string NetworkState { get { return _networkState; } set { SetProperty(ref _networkState, value); } }

        private string _connectState;
        public string ConnectState { get { return _connectState; } set { SetProperty(ref _connectState, value); } }
        
        private DelegateCommand accessCommand;
        public DelegateCommand AccessCommand => accessCommand ?? (accessCommand = new DelegateCommand(ExecuteAccess));

        private void ExecuteAccess()
        {
            //주어진 ip, port로 서버 엑세스
            EndPoint endPoint = new EndPoint(IP, Port);
            _client.SetEndPoint(endPoint);
            
            if(_client.Connect() == true)
            {
                NetworkState = "입력됨.";
                EqualsEnable = true;
            }
            else
            {
                EqualsEnable = false;
            }

        }

        //사용 중 연결끊길경우 호출
        private void TryConnect()
        {
            for(int tryCnt = 0; tryCnt < 5; tryCnt++)
            {
                if(false)//재접속시도
                {
                    break;
                }
                ConnectState = $"Reconnecting({tryCnt}/5)";
            }
        }
        #endregion

        #region Calculator
        //계산기 변수
        private string _formula;
        public string Formula { get { return _formula; } set { SetProperty(ref _formula, value); } }

        private string _checkValue;
        public string CheckValue { get { return _checkValue; } set { SetProperty(ref _checkValue, value); } }

        private string _treeValue;
        public string TreeValue { get { return _treeValue; } set { SetProperty(ref _treeValue, value); } }

        private string _result;
        public string Result { get { return _result; } set { SetProperty(ref _result, value); } }

        private ObservableCollection<Log> _logs;
        public ObservableCollection<Log> Logs
        {
            get { return _logs; }
            set { SetProperty(ref _logs, value); }
        }

        private bool _equalsEnable;
        public bool EqualsEnable { get { return _equalsEnable; } set { SetProperty(ref _equalsEnable, value); } }

        private DelegateCommand calculateCommand;
        public DelegateCommand CalculateCommand => calculateCommand ?? (calculateCommand = new DelegateCommand(ExecuteCalculate));

        private DelegateCommand exceptionThrow;

        public DelegateCommand ExceptionThrow => exceptionThrow ?? (exceptionThrow = new DelegateCommand(exceptionThrowCommand));


        private DelegateCommand calculateFileCommand;

        public DelegateCommand CalculateFileCommand => calculateFileCommand ?? (calculateFileCommand = new DelegateCommand(ExecuteFileCalculate));

        private void exceptionThrowCommand()
        {
            throw new Exception("Hello");
        }
        private void ExecuteFileCalculate()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                readExpsFromFile(openFileDialog.FileName);
            }
        }

        private void ExecuteCalculate()
        {
            //값 체크(안쓸것같음)
            CheckValue = true.ToString();

            if (Formula!=null)
            {
                //Tree 코드 변환
                try
                {
                    TreeValue = "Tree";

                    IntPtr ptr = retString(Formula);
                    string Message = Marshal.PtrToStringAnsi(ptr);
                    Marshal.FreeHGlobal(ptr);
                    if (Message == null)
                    {
                        Result = "잘못된 입력입니다.";
                    }
                    else if (Message.Contains("error")) {
                        Result = Message.Replace("error", "");
                    }
                    else
                    {
                        _client.Send(Message + System.Environment.NewLine);

                        //연산 결과 표시
                        Result = _client.Recv();
                    }
                    
                    if (Result != "")
                    {
                        Logs.Add(new Log(Formula, TreeValue, Result));
                    }
                }catch(Exception e)
                {
                    MessageBox.Show(e.ToString());

                }

            }
        }
        #endregion

        #region FileImport

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
                readExpsFromFile(ofdlg.FileName);
            }
        }

        //전달 받은 경로의 파일로 부터 수식 읽어옴.
        void readExpsFromFile(string path)
        {
            //파일로 부터 수식을 읽어옴
            string[] expsFromFile = File.ReadAllLines(@path);

            //수식 라인별로 수행
            foreach (string exp in expsFromFile)
            {
                string clearExp = exp.Trim();
                ExecuteCalculateFile(clearExp);
            }
        }

        private void ExecuteCalculateFile(string exp)
        {
            CheckValue = true.ToString();

            if (exp != null)
            {
                //Tree 코드 변환
                try
                {
                    TreeValue = "Tree";

                    IntPtr ptr = retString(exp);
                    string Message = Marshal.PtrToStringAnsi(ptr);
                    Marshal.FreeHGlobal(ptr);
                    if (Message == null)
                    {
                        Result = "잘못된 입력입니다.";
                    }
                    else if (Message.Contains("error"))
                    {
                        Result = Message.Replace("error", "");
                    }
                    else
                    {
                        _client.Send(Message + System.Environment.NewLine);

                        //연산 결과 표시
                        Result = _client.Recv();
                    }

                    if (Result != "")
                    {
                        Logs.Add(new Log(Formula, TreeValue, Result));
                    }
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());

                }

            }
        }


        #endregion


    }

}