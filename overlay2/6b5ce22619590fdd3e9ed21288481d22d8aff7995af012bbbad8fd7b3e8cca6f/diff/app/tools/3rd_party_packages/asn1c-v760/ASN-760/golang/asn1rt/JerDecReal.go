func (r *Real) UnmarshalJSON(data []byte) error {
	var val interface{}
	var err error

	err = json.Unmarshal(data, &val)
	if err != nil {
		return err
	}

	switch i := val.(type) {
	case map[string]interface{}:
		/* JSON Object.  It should contain just base10Value */
		if len(i) != 1 {
			return fmt.Errorf("Too many keys for REAL JSON object")
		}
		b10Val, present := i["base10Value"]
		if present {
			var floatval float64
			floatval, ok := b10Val.(float64)
			if !ok {
				return fmt.Errorf("Unexepcted type for base10Value")
			}
			*r = Real(floatval)
		} else {
			return fmt.Errorf("Missing base10Value key")
		}
	case string:
		if i == "INF" {
			*r = Real(math.Inf(1))
		} else if i == "-INF" {
			*r = Real(math.Inf(-1))
		} else if i == "NaN" {
			*r = Real(math.NaN())
		} else if i == "-0" {
			*r = Real(math.Copysign(0, -1))
		} else {
			return fmt.Errorf("Invalid JSON string for REAL")
		}
	case float64:
		*r = Real(i)
	default:
		return fmt.Errorf("Unexpected type for REAL")
	}

	return nil
}

func (r *RealBase10) UnmarshalJSON(data []byte) error {
	var floatval float64
	var err error
	err = json.Unmarshal(data, &floatval)
	if err != nil {
		return err
	}
	*r = RealBase10(strconv.FormatFloat(floatval, 'g', -1, 64))

	return nil
}

