#include <http_client.h> 
#include <ppltasks.h>
#include <json.h>


public class Speaker
{
	public int speaker_ID{ get; set; }

	public string Speaker_name{ get; set; }

	public double Volume{ get; set; }

	public double Xcoord{ get; set; }

	public double Ycoord{ get; set; }

	public double Zcoord{ get; set; }
}

public class Kinect
{
	public int kinect_ID{ get; set; }

	public double Xcoord{ get; set; }

	public double Ycoord{ get; set; }

	public double Zcoord{ get; set; }
}

public class Person
{
	public int Person_ID{ get; set; }

	public double Xcoord{ get; set; }

	public double Ycoord{ get; set; }

	public double Zcoord{ get; set; }
}

public class Speakers
{
	private Collection<Speaker> speakers = new Collection<Speaker>();

	private int nextId = 1;

	public Speaker Add(string speaker_name, double xcoord, double ycoord, double zcoord, double volume)
	{
		var speaker = new Speaker()
		{
			speaker_ID = nextId++,
			Speaker_name = speaker_name,
			Xcoord = xcoord,
			Ycoord = ycoord,
			Zcoord = zcoord,
			Volume = volume
		};

		speakers.Add(speaker);

		return speaker;
	}

	public IEnumerable<Speaker> GetAll()
	{
		return speakers;
	}

	public Speaker Get(int id)
	{
		return speakers.FirstOrDefault(s = > s.speaker_ID == id);
	}

	public Speaker Update(int id, string speaker_name, double xcoord, double ycoord, double zcoord, double volume)
	{
		var item = Get(id);
		if (item != null)
		{
			item.Speaker_name = speaker_name;
			item.Xcoord = xcoord;
			item.Ycoord = ycoord;
			item.Zcoord = zcoord;
			item.Volume = volume;
			return item;
		}

		return null;
	}

	public bool Delete(int id)
	{
		var item = Get(id);
		if (item != null)
		{
			speakers.Remove(item);
			return true;
		}

		return false;
	}
}

public class ValuesController : ApiController
{
	static ValuesController()
	{
		speakerss.Add("Speaker 1", 20.0, 0.0, 0.0, 70.0);
		//members.Add("Andrew", "Baseball");
		// . . .
	}

	private static Speakers speakers = new Speakers();

	// GET api/values
	public IEnumerable<Speaker> Get()
	{
		return speakers.GetAll();
	}

	// GET api/values/id
	public Speakers Get(int id)
	{
		return speakers.Get(id);
	}

	// POST api/values
	public int Post(dynamic data)
	{
		return speakers.Add((string)data.speaker_name, (double)data.xcoord, (double)data.ycoord, (double)data.zcoord, (double)data.volume ).SpeakerID;
	}

	// PUT api/values/id
	public Member Put(int id, dynamic data)
	{
		return spakers.Update(id, (string)data.speaker_name, (double)data.xcoord, (double)data.ycoord, (double)data.zcoord, (double)data.volume);
	}

	// DELETE api/values/id
	public bool Delete(int id)
	{
		return speakers.Delete(id);
	}
}

enum SpeakerValue { speaker_ID, Speaker_name, Xcoord, Ycoord, Zcoord, Volume };

class SpeakerGenerator
{
	std::map<std::wstring, FieldValue> fieldMap;
	Speaker speaker;

public:
	SpeakerGenerator()
	{
		fieldMap[L"speaker_ID"] = FieldValue::speakerID;
		fieldMap[L"Speaker_name"] = FieldValue::speaker_name;
		fieldMap[L"Xcoord"] = FieldValue::Xcoord;
		fieldMap[L"Ycoord"] = FieldValue::Ycoord;
		fieldMap[L"Zcoord"] = FieldValue::Zcoord;
	}

	//check here for errors not too sure about this
	void SetField(std::wstring speaker_name, json::value value)
	{
		switch (fieldMap[speaker_name])
		{
		case FieldValue::Speaker_ID:
			speaker.Speaker_ID = value.as_integer();
			break;

		case FieldValue::Speaker_name:
			speaker.Speaker_name = value.as_string();
			break;

		case FieldValue::Xcoord:
			speaker.Xcoord = value.as_double();
			break;
		case FieldValue::Ycoord:
			speaker.Ycoord = value.as_double();
			break;
		case FieldValue::Zcoord:
			speaker.Zcoord = value.as_double();
			break;
		}
	}

	Member GetSpeakerFromJson(json::value jsonValue)
	{
		for (auto iterInner = jsonValue.cbegin(); iterInner != jsonValue.cend(); ++iterInner)
		{
			const json::value &propertySpeaker_name = iterInner->first;
			const json::value &propertyValue = iterInner->second;

			SetField(propertySpeaker_name.as_string(), propertyValue);
		}

		return speaker;
	}
};


pplx::task<void> Get(int id)
{
	return pplx::create_task([id]
	{
		std::wstringstream ws;
		ws << L"http://KinectAudioVis.cloudapp.net" << id;
		http_client client(ws.str());

		return client.request(methods::GET);
	}).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}

		return pplx::create_task([] { return json::value(); });

	}).then([](json::value jsonValue)
	{
		if (jsonValue.is_null())
			return;

		SpeakerGenerator generator;
		auto speaker = generator.GetSpeakerFromJson(jsonValue);
		speaker.Display();
	});
}

pplx::task<int> Post()
{
	return pplx::create_task([]
	{
		json::value postData;
		postData[L"speaker_name"] = json::value::string(L"Joe Smith");
		postData[L"xcoord"] = json::value::double(20.0);
		postData[L"ycoord"] = json::value::double(0.0);
		postData[L"zcoord"] = json::value::double(0.0);
		postData[L"volume"] = json::value::double(50.0);

		http_client client(L"http://KinectAudioVis.cloudapp.net");
		return client.request(methods::POST, L"",
			postData.to_string().c_str(), L"application/json");
	}).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			auto body = response.extract_string();
			std::wcout << L"Added new Id: " << body.get().c_str() << std::endl;

			return std::stoi(body.get().c_str());
		}

		return 0;
	});
}

pplx::task<void> Put(int id)
{
	return pplx::create_task([id]
	{
		json::value postData;
		postData[L"speaker_name"] = json::value::string(L"Joe Smith");
		postData[L"xcoord"] = json::value::double(20.0);
		postData[L"ycoord"] = json::value::double(0.0);
		postData[L"zcoord"] = json::value::double(0.0);
		postData[L"volume"] = json::value::double(50.0);

		std::wstringstream ws;
		ws << L"http://KinectAudioVis.cloudapp.net" << id;
		http_client client(ws.str());

		return client.request(methods::PUT, L"",
			postData.to_string().c_str(), L"application/json");
	}).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			auto body = response.extract_string();
			std::wcout << L"Updated: " << body.get().c_str() << std::endl;
		}
	});
}

pplx::task<void> Delete(int id)
{
	return pplx::create_task([id]
	{
		std::wstringstream ws;
		ws << L"http://KinectAudioVis.cloudapp.net" << id;
		http_client client(ws.str());

		return client.request(methods::DEL);

	}).then([](http_response response)
	{
		if (response.status_code() == status_codes::OK)
		{
			auto body = response.extract_string();

			std::wcout << L"Deleted: " << body.get().c_str() << std::endl;
		}
	});
}

void main() {

	GetAll().then([]
	{
		Post().then([](int newId)
		{
			Get(newId).then([newId]
			{
				Put(newId).then([newId]
				{
					GetAll().then([newId]
					{
						Delete(newId).then([]
						{
							GetAll();
						});
					});
				});
			});
		});
	});
}