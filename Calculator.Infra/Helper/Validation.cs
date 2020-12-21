using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Infra.Helper
{
    public class Validation
    {
        public static KeyValuePair<bool, string> CheckIP(string ip)
        {
            if(ip == null) return new KeyValuePair<bool, string>(false, null);

            ip = ip.Replace(" ", "");

            //(검사하는 내용이 들어감)
            bool result = false;

            return new KeyValuePair<bool, string>(result, ip);
        }
    }
}
