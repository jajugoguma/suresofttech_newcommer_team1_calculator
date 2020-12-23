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

        //계산기 현재 값에 입력 처리
        public static string Add(string value, string tail)
        {
            DivisionHead(ref value);
            RemoveComma(ref value);

            value = value + tail;

            AppendComma(ref value);

            return head + value;
        }

        //계산기 현재 값 BackSpace 처리
        public static string BackSpace(string value)
        {
            DivisionHead(ref value);
            RemoveComma(ref value);

            value = value.Substring(0, value.Length - 1);

            if (!value.Equals(""))
                AppendComma(ref value);

            return value;
        }

        //양수 => 음수, 음수 => 양수
        public static string ChangePlusMinus(string value)
        {
            if (value[0].Equals('-'))
                value = value.Substring(1, value.Length - 1);
            else
                value = '-' + value;

            return value;
        }


        public static string InputOperator(string history, string value, char oprerator)
        {
            int cutsize = history.Length;

            if (value.Equals(""))
                cutsize = history.Length - 1;
            else if (value[0].Equals('-'))
                value = $"({value})";

            return history.Substring(0, cutsize) + value + oprerator;
        }

        //소수점 기준으로 분리
        public static string[] spliter(string value)
        {
            string[] num = value.Split('.');
            return num;
        }

        //정수형인지 실수형인지 확인해서 실수형인 경우 반올림 처리
        public static string typeChecker(string[] sval, int ival) 
        {
            bool flag = false;
            string answer = "";

            foreach (var i in sval[1])
            {
                if (i != '0')
                {
                    flag = true;
                    break;
                }
            }

            if (flag) //실수인 경우
            {
                if (sval[1].Length > ival && sval[1][ival] >= '5') //(자리수가 있고) 반올림 해야하는 경우
                {
                    //index 0~ival-1 까지 정수화 -> +1 -> string화
                    int outValue;
                    outValue = Convert.ToInt32(sval[0]);
                    outValue = Convert.ToInt32(sval[1].Substring(0,ival));
                    outValue++;
                }
            }
            else //정수인 경우
            {
                answer += sval[0];
            }
            return answer;
        }


        //괄호..
        public static string InputBracket()
        {
            return "";
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
