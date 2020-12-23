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
        private string _ip;
        public string IP
        {
            get { return _ip; }
            set { SetProperty(ref _ip, value); }
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
            if (!Validation.CheckIP(IP))
            {
                Text = "IP가 올바르지 않습니다.";
                //Views.PopupView model = new Views.PopupView();
                
                
                //model.ShowDialog();

                ////testcode
                //_eventAggregator.GetEvent<SendPopupOption>()
                //    .Publish(new Tuple<string, string, string>("Warning", "IP가 올바르지 않습니다", "Retry"));
                return;
            }

            EndPoint endPoint = new EndPoint(IP, Port);
            _repository.Client.SetEndPoint(endPoint);

            if (_repository.Client.Connect() == true)
            {
                Text = "연결 성공";
                _eventAggregator.GetEvent<SendNetworkStateEvent>().Publish(true);
            }
            else
            {
                Text = "연결 실패";
                _eventAggregator.GetEvent<SendNetworkStateEvent>().Publish(false);
            }
        }

        public NetworkViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;

            IP = _repository.IP;
            Port = _repository.Port;
        }


    }
}
