
using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using Calculator.Infra.Model;
using System.Windows.Data;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;

namespace Calculator.ViewModels
{
    class MainWindowViewModel : BindableBase
    {

        public MainWindowViewModel()
        {
            EqualsEnable = false;
            _logs = new ObservableCollection<Log>();
        }


        #region Network
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

            NetworkState = "입력됨.";
            EqualsEnable = true;
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

        private void ExecuteCalculate()
        {
            //값 체크(안쓸것같음)
            CheckValue = true.ToString();

            if (true)
            { 
                //Tree 코드 변환
                TreeValue = "Tree";

                //연산 결과 표시
                Result = Formula;

                Logs.Add(new Log(Formula, TreeValue, Result));
            }
        }
        #endregion

        #region FileImport
        
        //전달 받은 경로의 파일로 부터 수식 읽어옴.
        void readExpsFromFile(string path)
        {
            //파일로 부터 수식을 읽어옴
            string[] expsFromFile = File.ReadAllLines(@path);

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



        #endregion


    }

}