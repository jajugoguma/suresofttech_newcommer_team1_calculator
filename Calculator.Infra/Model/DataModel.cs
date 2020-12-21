using Prism.Mvvm;

namespace Calculator.Infra.Model
{
    public class Log
    {
        public string Formula { get; set; }
        public string Tree { get; set; }
        public string Result { get; set; }

        public Log(string formula, string tree, string result)
        {
            Formula = formula;
            Tree = tree;
            Result = result;
        }
    }


    public class Option
    {
        public string TailCnt { get; set; } //소수점
    }
}
