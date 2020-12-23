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

namespace Calculator.ViewModels
{
    class SettingViewModel : BindableBase
    {
        IRepository _repository;

        private int tailCnt;
        public int TailCnt
        {
            get { return tailCnt; } 
            set { SetProperty(ref tailCnt, value); }
        }

        private bool serverCalculateFlagCheck;

        public bool ServerCalculateFlagCheck
        {
            get { return serverCalculateFlagCheck; }
            set { SetProperty(ref serverCalculateFlagCheck, value); }
        }

        private DelegateCommand checkButtonCommand;
        public DelegateCommand CheckButtonCommand => checkButtonCommand ?? (checkButtonCommand = new DelegateCommand(Check));
        private void Check()
        {
             _repository.TailCnt = TailCnt;
            _repository.ServerCalculateFlagCheck = ServerCalculateFlagCheck;
        }

        public SettingViewModel(IRepository repository)
        {
            _repository = repository;

            TailCnt = _repository.TailCnt;
            ServerCalculateFlagCheck = _repository.ServerCalculateFlagCheck;
        }
    }
}
