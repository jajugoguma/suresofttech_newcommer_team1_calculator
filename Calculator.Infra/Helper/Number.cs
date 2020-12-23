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
            {
                if (!(history[history.Length - 1] == ')'))
                {
                    cutsize = history.Length - 1;
                    return history.Substring(0, cutsize) + oprerator;
                }
            }
            else if (value[0].Equals('-'))
                value = $"({value})";

            return history.Substring(0, cutsize) + value + oprerator;
        }

        public static string ExcuteDot(string value, int tailCnt)
        {
            string[] sval = value.Split('.');
            string[] trash = sval[1].Split('@');
            sval[1] = trash[0];
            int ival = tailCnt;

            bool typeDOUBLE = false;
            string answer = "";

            //정수형인지 실수형인지 확인 : 소수점 이하 숫자 중 '0'이 아닌 문자가 하나라도 포함된 경우, 실수 판정
            foreach (var i in sval[1])
            {
                if (i != '0')
                {
                    typeDOUBLE = true;
                    break;
                }
            }

            //실수인 경우 반올림 처리
            if (typeDOUBLE) //실수일 때
            {
                if (sval[1].Length > ival) //반올림할 자리수가 있을 때
                {
                    if (sval[1][ival] >= '5') //반올림 해야할 때
                    {
                        //index 0~ival-1 까지 정수화 -> +1 -> string화
                        string snum = "";
                        int inum = 0;

                        snum += sval[0] + sval[1].Substring(0, ival);
                        inum = Convert.ToInt32(snum);

                        inum++;
                        answer += inum.ToString();
                        if (ival == 0)
                        {
                            ;
                        }
                        else if (snum.Length != answer.Length)
                        {
                            answer = answer.Insert(sval[0].Length + 1, ".");
                        }
                        else
                        {
                            answer = answer.Insert(sval[0].Length, ".");
                        }
                    }
                    else //반올림 없을 때 : 잘라서 붙임
                    {
                        answer += sval[0];
                        answer += '.';
                        answer += sval[1].Substring(0, ival);
                    }
                }
                else //반올림할 자리수가 없을 때 : 그냥 붙임
                {
                    answer += sval[0];
                    answer += '.';
                    answer += sval[1];
                }

            }
            else //정수인 경우
            {
                answer += sval[0];
            }
            return answer;
        }

       
        //괄호.. 추가함
        public static string OpenBracket(string history, string value, char bracket)
        {
            DivisionHead(ref value);

            //###############################새코드
            int cutsize = history.Length - 1;
            //히스토리가 비어있으면
            if (history.Equals(""))
            {
                //괄호 열기 추가
                return history + value + bracket;
            }
            //히스토리의 마지막 글자가 연산자 이거나 괄호열기면 괄호열기 추가
            else if (history[cutsize] == '+' || history[cutsize] == '-' || history[cutsize] == '/' || history[cutsize] == '*' || history[cutsize] == '(')
            {
                return history + value + bracket;
            }

            //히스토리가 비어있지 않고 연산자와 괄호열기로 끝난게 아니면(즉, 숫자로 끝남) 그냥 현재 숫자 붙여서 히스토리 저장
            return history + value;
            //###############################

            /* 기존코드
            if (value.Replace("(", "").Equals(""))
                value = value + "(";

            return head + value;
            */
        }
        public static string CloseBracket(string history, string value, char bracket)
        {
            //###############################새코드
            int a;
            int cutsize = history.Length - 1;
            //입력값 없을때
            if (value.Equals(""))
            {
                //히스토리의 마지막이 괄호 닫기면
                if (history[cutsize] == ')')
                {
                    //괄호 닫기 추가
                    return history + value + bracket;
                }  
            }
            //입력값이 있는데 그 값이 숫자면
            else if (int.TryParse(value, out a))
            {
                //히스토리에 해당 수와 괄호 닫기 추가
                return history + value + bracket;
            }

            return history + value;
            //###############################

            //if(value[value.Length - 1]) 

            //return "";
        }

        //헤드 분리
        private static void DivisionHead(ref string value)
        {
            
            head = value.Contains("-") ? "-" : "";
            value = value.Replace("-", "");
        }

        private static void AppendComma(ref string value)
        {
            /*
            int left = 0;
            int right = 0;

            if (value.Contains("("))
            {
                int index = 0;
                while (value[index++] == '(')
                {
                    left++;
                    value.Substring(1, value.Length);
                }
            }

            if (value.Contains(")"))
            {
                int index = value.Length - 1;
                while (value[index--] == ')')
                {
                    right++;
                    value.Substring(0, value.Length - 1);
                }
            }
            */
            value = string.Format("{0:#,0}", Convert.ToInt64(value)).ToString();
        }

        private static void RemoveComma(ref string value)
        {
            if (value.Length > 4)
                value = value.Replace(",", "");
        }
    }

}
