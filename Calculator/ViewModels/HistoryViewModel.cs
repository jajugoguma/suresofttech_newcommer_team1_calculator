using Prism.Mvvm;
using Prism.Events;
using Prism.Commands;

using System.Collections.ObjectModel;

using Calculator.Infra.Service;
using Calculator.Infra.Model;
using Calculator.Infra.Event;

namespace Calculator.ViewModels
{
    class HistoryViewModel : BindableBase
    {
        private IRepository _repository;
        private IEventAggregator _eventAggregator;

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

        private DelegateCommand<string> _sendTreeValueCommand;
        public DelegateCommand<string> SendTreeValueCommand => _sendTreeValueCommand ?? (_sendTreeValueCommand = new DelegateCommand<string>(SendTreeValue));
        private void SendTreeValue(string data)
        {
            _eventAggregator.GetEvent<SendTreeViewerDataEvent>().Publish("testsetseata");
        }

        private DelegateCommand _resetCommand;
        public DelegateCommand ResetLogCommand => _resetCommand ?? (_resetCommand = new DelegateCommand(Reset));
        private void Reset()
        {
            _repository.ResetLog();
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
