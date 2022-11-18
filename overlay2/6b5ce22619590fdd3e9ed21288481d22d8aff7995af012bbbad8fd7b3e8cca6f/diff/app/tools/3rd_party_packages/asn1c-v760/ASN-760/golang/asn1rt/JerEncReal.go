func (r Real) MarshalJSON() ([]byte, error) {
	/* special real values for +/- oo, NAN, -0 */
	if math.IsInf(float64(r), -1) {
		return json.Marshal("-INF")
	} else if math.IsInf(float64(r), 1) {
		return json.Marshal("INF")
	} else if math.IsNaN(float64(r)) {
		return json.Marshal("NaN")
	} else if r == 0.0 && math.Signbit(float64(r)) {
		/* -0.0 */
		return json.Marshal("-0")
	} else {
		/* 0 or any base 2 value */
		return json.Marshal(float64(r))
	}
}

func (r RealBase10) MarshalJSON() ([]byte, error) {
	/* We assume value must be 0 or base 10. */
	var err error
	var floatval float64
	floatval, err = strconv.ParseFloat(string(r), 64)
	if err != nil {
		return nil, err
	}

	return json.Marshal(floatval)
}