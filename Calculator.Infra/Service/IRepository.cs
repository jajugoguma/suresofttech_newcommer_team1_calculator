﻿using Calculator.Infra.Model;
using System.Collections.Generic;

namespace Calculator.Infra.Service
{
    public interface IRepository
    {
        List<Log> LogList { get; }       
    }
}
