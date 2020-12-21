using Prism.Events;
using Prism.Mvvm;
using Prism.Commands;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Calculator.Infra.Event;
namespace Calculator.ViewModels
{
    class PopupViewModel : BindableBase
    {
        private IEventAggregator _eventAggregator;
        private string _title;
        public string Title
        {
            get { return _title; }
            set { SetProperty(ref _title, value); }
        }

        private string _popupText;
        public string PopupText
        {
            get { return _popupText; }
            set { SetProperty(ref _popupText, value); }
        }

        private string _buttonText;
        public string ButtonText
        {
            get { return _buttonText; }
            set { SetProperty(ref _buttonText, value); }
        }


        private DelegateCommand okCommand;
        public DelegateCommand OKCommand => okCommand ?? (okCommand = new DelegateCommand(ReturnOK));
        private void ReturnOK()
        {
            //return Prism.Services.Dialogs.DialogResult.OK;
        }


        public PopupViewModel(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;

            _eventAggregator.GetEvent<SendPopupOption>().Subscribe(SetPopup);

            PopupText = "오 픈 ";
        }

        public void SetPopup(Tuple<string, string, string> data)
        {//string title, string popup, string button
            
            Title = data.Item1;
            PopupText = data.Item2;
            ButtonText = data.Item3;
        }
    }
}
