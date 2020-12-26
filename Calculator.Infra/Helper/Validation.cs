using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator.Infra.Helper
{
    public class Validation
    {
        public static bool CheckIP(string ip)
        {
            if(ip == null) return false;

            bool result = false;

            ip = ip.Replace(" ", "");
            string[] ips = ip.Split('.');

            int n;

            if(ips.Length != 4)
            {
                return false;
            }
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


            return result;
        }
    }
}
