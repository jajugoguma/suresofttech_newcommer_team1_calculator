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

        private DelegateCommand connectServerCommand;
        public DelegateCommand ConnectServerCommand => connectServerCommand ?? (connectServerCommand = new DelegateCommand(ConnectServer));
        private void ConnectServer()
        {
            //주어진 ip, port로 서버 엑세스
            EndPoint endPoint = new EndPoint(IP, Port);
            _repository.Client.SetEndPoint(endPoint);


            if(_repository.Client.Connect())
            {

            }
            else
            {
                PopupViewModel model = new PopupViewModel("Warning", "연결 할 수 없습니다", "Retry");
            }
        }

        public NetworkViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;
        }


    }
}
