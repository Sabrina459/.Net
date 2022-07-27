using System.Linq;
using BusinessLogic;
using DataBase.EF;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.EntityFrameworkCore;
using Microsoft.OpenApi.Models;
using Ninject;
using Ninject.Modules;
using System.Web;
using System.Web.Mvc;
using DataBase.Entities;
using DataBase.Interfaces;
using DataBase.Repository;
using Ninject.Web.WebApi;

namespace PresentationLayer
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddControllers();
            services.AddDbContext<GoodContext>(options => options.UseSqlServer(Configuration["ConnectionString:connectionString"]));
            services.AddTransient<IUnitOfWork, EFUnitOfWork>();
            services.AddTransient<IOrderService, OrderService>().;
            /*services.AddTransient<IRepository<Good>, GoodRepository>();
            services.AddTransient<IRepository<Order>, OrderRepository>();*/
            services.AddSwaggerGen(c =>
            {
                c.SwaggerDoc("v1", new OpenApiInfo {Title = "PresentationLayer", Version = "v1"});
                c.ResolveConflictingActions (apiDescriptions => apiDescriptions.First ());
            });
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
                app.UseSwagger();
                app.UseSwaggerUI(c => c.SwaggerEndpoint("/swagger/v1/swagger.json", "PresentationLayer v1"));
            }

            app.UseHttpsRedirection();

            app.UseRouting();

            app.UseAuthorization();

            app.UseEndpoints(endpoints => { endpoints.MapControllers(); });
        }
    }
}