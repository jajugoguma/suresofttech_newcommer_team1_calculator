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

            bool result = false;

            ip = ip.Replace(" ", "");
            string[] ips = ip.Split('.');

            int n;
            foreach (string tmp in ips)
            {
                if (false == int.TryParse(tmp, out n))
                {
                    result = false;
                }
                else
                {
                    n = Int32.Parse(tmp);
                    result = (n >= 0 && n <= 255);
                }
            }


            return new KeyValuePair<bool, string>(result, ip);
        }
    }
}
