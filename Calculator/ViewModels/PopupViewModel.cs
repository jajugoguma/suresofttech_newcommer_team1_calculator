using Prism.Events;
using Prism.Mvvm;
using Prism.Commands;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.ViewModels
{
    class PopupViewModel : BindableBase
    {
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

        public PopupViewModel(string title, string popup, string button)
        {
            Title = title;
            PopupText = popup;
            ButtonText = button;
        }
    }
}
