import urllib.request
import json
Wea_url = "https://free-api.heweather.com/s6/weather/now?location=CN101070201&key=e5a835b982ba40d9a897b42b5b8c883f"
Lif_url = "https://free-api.heweather.com/s6/weather/lifestyle?location=CN101070201&key=e5a835b982ba40d9a897b42b5b8c883f"
Air_url = "https://free-api.heweather.com/s6/air/now?location=CN101070201&key=e5a835b982ba40d9a897b42b5b8c883f"
def getWeather(url):
    data = urllib.request.urlopen(url).read()
    txt = data.decode(encoding="utf-8",errors="strict")
    print("orig_data:\n",txt)    
    dejson = json.loads(txt)
    deal_data(dejson)

def deal_data(json):
    if(isinstance(json,dict)):
        for i in list(json.keys()):
            if(isinstance(json[i],list)):
                for i in json[i]:
                    deal_data(i)
            else:
                deal_data(json[i])
    else:
        print(json)

if __name__ == '__main__':
    getWeather(Wea_url)
    getWeather(Air_url)
    getWeather(Lif_url)
