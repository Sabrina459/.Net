FROM mcr.microsoft.com/dotnet/runtime:5.0 AS base
WORKDIR /app

FROM mcr.microsoft.com/dotnet/sdk:5.0 AS build
WORKDIR /src
COPY ["DesktopClient/DesktopClient.csproj", "DesktopClient/"]
RUN dotnet restore "DesktopClient/DesktopClient.csproj"
COPY . .
WORKDIR "/src/DesktopClient"
RUN dotnet build "DesktopClient.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "DesktopClient.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "DesktopClient.dll"]
