using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Prism.Events;
using Calculator.Infra.Event;
namespace Calculator.Views
{
    /// <summary>
    /// CalCulatorView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class CalculatorView : Window
    {
        IEventAggregator _eventAggregator;
        public CalculatorView(IEventAggregator eventAggregator)
        {            
            InitializeComponent();

            _eventAggregator = eventAggregator;


            Closing += (x, y) => { System.Windows.Application.Current.Shutdown(); };
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            //MessageBox.Show(e.Key.ToString());

            //숫자 입력
            if (!(Keyboard.IsKeyDown(Key.LeftShift) || Keyboard.IsKeyDown(Key.RightShift)) && e.Key.ToString().Contains("D") && !e.Key.ToString().Contains("Divide"))
            {
                string inputNumber = e.Key.ToString().Replace("D", "");
                _eventAggregator.GetEvent<KeyInputNumberEvent>().Publish(inputNumber);
            }
            //Numpad 숫자 입력
            if (e.Key.ToString().Contains("NumPad") && !e.Key.ToString().Contains("Divide"))
            {
                string inputNumber = e.Key.ToString().Replace("NumPad", "");
                _eventAggregator.GetEvent<KeyInputNumberEvent>().Publish(inputNumber);
            }
            //더하기 입력
            if (isPlusPressed(sender, e))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("plus");
            }
            //나누기 입력
            if (isDividePressed(sender, e))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("division");
            }
            //빼기 입력
            if (isMinusPressed(sender, e))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("minus");
            }
            //곱하기 입력
            if (isMultiplyPressed(sender, e))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("multiply");
            }
            //esc 입력
            if (Keyboard.IsKeyDown(Key.Escape))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("reset");
            }
            //엔터 입력
            if (Keyboard.IsKeyDown(Key.Return))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("equal");
            }
            //백스페이스 입력
            if (Keyboard.IsKeyDown(Key.Back))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("bs");
            }
            if (isOpenbracketPressed(sender, e))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("open");
            }
            if (isClosebracketPressed(sender, e))
            {
                _eventAggregator.GetEvent<KeyInputEvent>().Publish("close");
            }
     

        }

        private bool isPlusPressed(object sender, KeyEventArgs e)
        {
            if (((Keyboard.IsKeyDown(Key.LeftShift) || Keyboard.IsKeyDown(Key.RightShift)) && Keyboard.IsKeyDown(Key.OemPlus)) 
                || Keyboard.IsKeyDown(Key.Add))
            {
                return true;
            } 
            return false;
        }

        private bool isDividePressed(object sender, KeyEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.OemQuestion) || Keyboard.IsKeyDown(Key.Divide))
            {
                return true;
            }
            return false;
        }

        private bool isMinusPressed(object sender, KeyEventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.OemMinus) || Keyboard.IsKeyDown(Key.Subtract))
            {
                return true;
            }
            return false;
        }

        private bool isMultiplyPressed(object sender, KeyEventArgs e)
        {
            if (((Keyboard.IsKeyDown(Key.LeftShift) || Keyboard.IsKeyDown(Key.RightShift)) && Keyboard.IsKeyDown(Key.D8))
                || Keyboard.IsKeyDown(Key.Multiply))
            {
                return true;
            }
            return false;
        }

        private bool isOpenbracketPressed(object sender, KeyEventArgs e)
        {
            if ((Keyboard.IsKeyDown(Key.LeftShift) || Keyboard.IsKeyDown(Key.RightShift)) && Keyboard.IsKeyDown(Key.D9))
            {
                return true;
            }
            return false;
        }

        private bool isClosebracketPressed(object sender, KeyEventArgs e)
        {
            if ((Keyboard.IsKeyDown(Key.LeftShift) || Keyboard.IsKeyDown(Key.RightShift)) && Keyboard.IsKeyDown(Key.D0))
            {
                return true;
            }
            return false;
        }
    }
}
