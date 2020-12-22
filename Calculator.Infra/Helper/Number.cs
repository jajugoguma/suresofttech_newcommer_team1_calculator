using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Infra.Helper
{
    public static class Number
    {
        private static string head = "";

        public static string Add(string value, string tail)
        {
            DivisionHead(ref value);
            RemoveComma(ref value);

            value = value + tail;

            AppendComma(ref value);

            return head + value;
        }

        public static string BackSpace(string value)
        {
            DivisionHead(ref value);
            RemoveComma(ref value);

            value = value.Substring( 0, value.Length - 1);

            if(!value.Equals(""))
                AppendComma(ref value);

            return value;
        }

        public static string ChangePlusMinus(string value)
        {
            if (value[0].Equals('-'))
                value = value.Substring(1, value.Length - 1);
            else
                value = '-' + value;

            return value; 
        }

        //헤드 분리
        private static void DivisionHead(ref string value)
        {
            head = value.Contains("-") ? "-" : "";
            value = value.Replace("-", "");
        }

        private static void AppendComma(ref string value)
        {
            value = string.Format("{0:#,0}", Convert.ToInt64(value)).ToString();
        }

        private static void RemoveComma(ref string value)
        {
            if (value.Length > 4)
                value = value.Replace(",", "");
        }
    }
}
