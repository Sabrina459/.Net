FROM mcr.microsoft.com/dotnet/aspnet:5.0 AS base
WORKDIR /app
EXPOSE 80
EXPOSE 443

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["Lab5WebApi/Lab5WebApi.csproj", "Lab5WebApi/"]
RUN dotnet restore "Lab5WebApi/Lab5WebApi.csproj"
COPY . .
WORKDIR "/src/Lab5WebApi"
RUN dotnet build "Lab5WebApi.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "Lab5WebApi.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "Lab5WebApi.dll"]
