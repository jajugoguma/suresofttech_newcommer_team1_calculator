using Prism.Mvvm;
using Prism.Events;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Windows.Input;

using Calculator.Infra.Service;
using Calculator.Infra.Model;
using Calculator.Infra.Event;
using Prism.Commands;

namespace Calculator.ViewModels
{
    class HistoryViewModel : BindableBase
    {
        private IRepository _repository;
        private IEventAggregator _eventAggregator { get;  set; }

        private ObservableCollection<Log> logs;
        public ObservableCollection<Log> Logs
        {
            get { return logs; }
            set { SetProperty(ref logs, value);  }
        }

        private void UpdataLogs()
        {
            Logs = new ObservableCollection<Log>(_repository.LogList);
        }

        public HistoryViewModel(IRepository repository, IEventAggregator ea)
        {
            _repository = repository;
            _eventAggregator = ea;

            Logs = new ObservableCollection<Log>(_repository.LogList);

            _eventAggregator.GetEvent<UpdateLogEvent>().Subscribe(UpdataLogs);
        }
    }
}
