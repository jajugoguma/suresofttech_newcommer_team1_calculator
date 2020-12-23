using Prism.Mvvm;
using Prism.Events;
using Prism.Commands;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

using Calculator.Infra.Service;
using Calculator.Infra.Event;

namespace Calculator.ViewModels
{
    class SettingViewModel : BindableBase
    {
        IRepository _repository;
        private IEventAggregator _eventAggregator { get; }

        private int tailCnt;
        public int TailCnt
        {
            get { return tailCnt; } 
            set { SetProperty(ref tailCnt, value); }
        }

        private bool clientCalculateFlagCheck;

        public bool ClientCalculateFlagCheck
        {
            get { return clientCalculateFlagCheck; }
            set { SetProperty(ref clientCalculateFlagCheck, value); }
        }

        private DelegateCommand checkButtonCommand;
        public DelegateCommand CheckButtonCommand => checkButtonCommand ?? (checkButtonCommand = new DelegateCommand(Check));
        private void Check()
        {
             _repository.TailCnt = TailCnt;
            _repository.ClientCalculateFlagCheck = ClientCalculateFlagCheck;
            _eventAggregator.GetEvent<CaleServerFlagEvent>().Publish(ClientCalculateFlagCheck);

        }

        public SettingViewModel(IRepository repository, IEventAggregator eventAggregator)
        {
            _repository = repository;
            _eventAggregator = eventAggregator;


            TailCnt = _repository.TailCnt;
            ClientCalculateFlagCheck = _repository.ClientCalculateFlagCheck;
        }
    }
}
