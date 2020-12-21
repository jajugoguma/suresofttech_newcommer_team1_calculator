using Prism.Mvvm;
using Prism.Commands;
using Prism.Events;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Calculator.Infra.Service;
using CalendarNetworkClient;
using Calculator.Infra.Helper;
using Calculator.Infra.Event;

namespace Calculator.ViewModels
{
    class NetworkViewModel : BindableBase
    {
        private IRepository _repository;
        private IEventAggregator _eventAggregator;
        private string ip;
        public string IP
        {
            get { return ip; }
            set { SetProperty(ref ip, value); }
        }

        private string port;
        public string Port
        {
            get { return port; }
            set { SetProperty(ref port, value); }
        }

        private string _text;
        public string Text
        {
            get { return _text; }
            set { SetProperty(ref _text, value); }
        }


        private DelegateCommand connectServerCommand;
        public DelegateCommand ConnectServerCommand => connectServerCommand ?? (connectServerCommand = new DelegateCommand(ConnectServer));
        private void ConnectServer()
        {
            //test용
            KeyValuePair<bool, string> checkIP = Validation.CheckIP(ip);

            if (!checkIP.Key)
            {
                Text = "IP가 올바르지 않습니다.";
                Views.PopupView model = new Views.PopupView();
                
                
                model.ShowDialog();

                //testcode
                _eventAggregator.GetEvent<SendPopupOption>()
                    .Publish(new Tuple<string, string, string>("Warning", "IP가 올바르지 않습니다", "Retry"));
                
                
                return;
            }
            
            //주어진 ip, port로 서버 엑세스
            EndPoint endPoint = new EndPoint(ip, Port);
            _repository.Client.SetEndPoint(endPoint);


            if(_repository.Client.Connect())
            {

            }
            else
            {

            }
        }

        public NetworkViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;
        }


    }
}
