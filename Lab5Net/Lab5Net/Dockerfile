FROM mcr.microsoft.com/dotnet/aspnet:5.0 AS base
WORKDIR /app
EXPOSE 80
EXPOSE 443

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["Lab5Net/Lab5Net.csproj", "Lab5Net/"]
RUN dotnet restore "Lab5Net/Lab5Net.csproj"
COPY . .
WORKDIR "/src/Lab5Net"
RUN dotnet build "Lab5Net.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "Lab5Net.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "Lab5Net.dll"]
