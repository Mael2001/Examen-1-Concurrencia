using System;
using System.IO;
using System.Threading;
using System.Threading.Tasks;

namespace Ejercicio_2
{
    class Program
    {
        public static async Task RunAsync(CancellationToken token)
        {
            if (token.IsCancellationRequested)
            {
                return;
            }
            await File.WriteAllTextAsync(@"data\text.txt", "Starting process");
            for (int i = 0; i < 1000000; i++)
            {
                if (token.IsCancellationRequested)
                {
                    return;
                }
                System.Console.WriteLine($"Processing {i} in thread { Thread.CurrentThread.ManagedThreadId} ");
                await File.AppendAllTextAsync(@"data\text.txt", $"Processing {i} in thread { Thread.CurrentThread.ManagedThreadId} ");
            }
        }
        static async Task Main(string[] args)
        {
            Console.WriteLine("Ingrese Tiempo de espera para cancelacion de token en seg");
            int time = int.Parse(Console.ReadLine()) * 1000;
            Console.WriteLine(time);
            var cancellationToken = new CancellationTokenSource(time);
            await RunAsync(cancellationToken.Token);
        }
    }
}
