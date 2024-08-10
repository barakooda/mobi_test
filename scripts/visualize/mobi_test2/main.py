import json
from visualize import visualize_lanes
import pathlib


def load_json_as_dict(file_path: pathlib.Path) -> dict:
    try:
        with file_path.open('r') as file:
            return json.load(file)
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return {}
    except json.JSONDecodeError as e:
        print(f"Error decoding JSON: {e}")
        return {}


def main():
    # Use a relative path
    script_dir = pathlib.Path(__file__).parent.resolve()
    
    file_path = script_dir.parent.parent.parent / "resources/data/enhanced_map.json"
    print(file_path)
    data = load_json_as_dict(file_path)
    
    if 'lanes' in data:
        visualize_lanes(data.get('lanes'))
    else:
        print("No 'lanes' key found in the JSON data.")


if __name__ == '__main__':
    main()
