

	option_t complex_nine_convolution(surface& surf, three_3d_matrix& value)
	{
		if (surf.buffer_size > data::cache_buffer_size || data::cache_buffer == nullptr) return 1;
		data::cache_surface.end = data::cache_buffer + surf.buffer_size;

		surf >> data::cache_surface;

		three_3d_matrix sums;

		// bottom-left
		sums.blue.x11 = value.blue.x22 + value.blue.x23 + value.blue.x32 + value.blue.x33;
		sums.green.x11 = value.green.x22 + value.green.x23 + value.green.x32 + value.green.x33;
		sums.red.x11 = value.red.x22 + value.red.x23 + value.red.x32 + value.red.x33;

		// bottom-right
		sums.blue.x13 = value.blue.x22 + value.blue.x21 + value.blue.x32 + value.blue.x31;
		sums.green.x13 = value.green.x22 + value.green.x21 + value.green.x32 + value.green.x31;
		sums.red.x13 = value.red.x22 + value.red.x21 + value.red.x32 + value.red.x31;

		// top-left
		sums.blue.x31 = value.blue.x22 + value.blue.x23 + value.blue.x12 + value.blue.x13;
		sums.green.x31 = value.green.x22 + value.green.x23 + value.green.x12 + value.green.x13;
		sums.red.x31 = value.red.x22 + value.red.x23 + value.red.x12 + value.red.x13;

		// top-right
		sums.blue.x33 = value.blue.x22 + value.blue.x21 + value.blue.x12 + value.blue.x11;
		sums.green.x33 = value.green.x22 + value.green.x21 + value.green.x12 + value.green.x11;
		sums.red.x33 = value.red.x22 + value.red.x21 + value.red.x12 + value.red.x11;

		// bottom
		sums.blue.x12 = sums.blue.x11 + value.blue.x21 + value.blue.x31;
		sums.green.x12 = sums.green.x11 + value.green.x21 + value.green.x31;
		sums.red.x12 = sums.red.x11 + value.red.x21 + value.red.x31;

		// left
		sums.blue.x21 = sums.blue.x11 + value.blue.x12 + value.blue.x13;
		sums.green.x21 = sums.green.x11 + value.green.x12 + value.green.x13;
		sums.red.x21 = sums.red.x11 + value.red.x12 + value.red.x13;

		// top
		sums.blue.x32 = sums.blue.x31 + value.blue.x21 + value.blue.x11;
		sums.green.x32 = sums.green.x31 + value.green.x21 + value.green.x11;
		sums.red.x32 = sums.red.x31 + value.red.x21 + value.red.x11;

		// right
		sums.blue.x23 = sums.blue.x13 + value.blue.x11 + value.blue.x12;
		sums.green.x23 = sums.green.x13 + value.green.x11 + value.green.x12;
		sums.red.x23 = sums.red.x13 + value.red.x11 + value.red.x12;

		// middle
		sums.blue.x22 = sums.blue.x12 + value.blue.x11 + value.blue.x12 + value.blue.x13;
		sums.green.x22 = sums.green.x12 + value.green.x11 + value.green.x12 + value.green.x13;
		sums.red.x22 = sums.red.x12 + value.red.x11 + value.red.x12 + value.red.x13;

		const int
			t0o = surf.size.x << 2, b0o = -t0o,
			tl0o = t0o - 4, tr0o = t0o + 4,
			bl0o = b0o - 4, br0o = b0o + 4,

			tdl0o = t0o - 8,

			t1o = t0o | 1, t2o = t0o | 2,
			tl1o = tl0o | 1, tl2o = tl0o | 2,
			tr1o = tr0o | 1, tr2o = tr0o | 2,

			b1o = b0o | 1, b2o = b0o | 2,
			bl1o = bl0o | 1, bl2o = bl0o | 2,
			br1o = br0o | 1, br2o = br0o | 2;

		// bottom-left
		auto dp = UCHAR_PTR(surf.buffer);
		if (sums.blue.x11 != 0)
			dp[0] = (
				dp[0] * value.blue.x22 +
				dp[4] * value.blue.x23 +
				dp[t0o] * value.blue.x32 +
				dp[tr0o] * value.blue.x33
				) / sums.blue.x11;
		if (sums.green.x11 != 0)
			dp[1] = (
				dp[1] * value.green.x22 +
				dp[5] * value.green.x23 +
				dp[t1o] * value.green.x32 +
				dp[tr1o] * value.green.x33
				) / sums.green.x11;
		if (sums.red.x11 != 0)
			dp[2] = (
				dp[2] * value.red.x22 +
				dp[6] * value.red.x23 +
				dp[t2o] * value.red.x32 +
				dp[tr2o] * value.red.x33
				) / sums.red.x11;

		// bottom-right
		dp += tl0o;
		if (sums.blue.x13 != 0)
			dp[0] = (
				dp[0] * value.blue.x22 +
				dp[-4] * value.blue.x21 +
				dp[t0o] * value.blue.x32 +
				dp[tl0o] * value.blue.x31
				) / sums.blue.x13;
		if (sums.green.x13 != 0)
			dp[1] = (
				dp[1] * value.green.x22 +
				dp[-3] * value.green.x21 +
				dp[t1o] * value.green.x32 +
				dp[tl1o] * value.green.x31
				) / sums.green.x13;
		if (sums.red.x13 != 0)
			dp[2] = (
				dp[2] * value.red.x22 +
				dp[-2] * value.red.x21 +
				dp[t2o] * value.red.x32 +
				dp[tl2o] * value.red.x31
				) / sums.red.x13;

		// top-right
		dp = UCHAR_PTR(surf.end - 1);
		if (sums.blue.x33 != 0)
			dp[0] = (
				dp[0] * value.blue.x22 +
				dp[-4] * value.blue.x21 +
				dp[b0o] * value.blue.x12 +
				dp[bl0o] * value.blue.x11
				) / sums.blue.x33;
		if (sums.green.x33 != 0)
			dp[1] = (
				dp[1] * value.green.x22 +
				dp[-3] * value.green.x21 +
				dp[b1o] * value.green.x12 +
				dp[bl1o] * value.green.x11
				) / sums.green.x33;
		if (sums.red.x33 != 0)
			dp[2] = (
				dp[2] * value.red.x22 +
				dp[-2] * value.red.x21 +
				dp[b2o] * value.red.x12 +
				dp[bl2o] * value.red.x11
				) / sums.red.x33;

		// top-left
		dp -= tl0o;
		if (sums.red.x31 != 0)
			dp[0] = (
				dp[0] * value.blue.x22 +
				dp[4] * value.blue.x23 +
				dp[b0o] * value.blue.x12 +
				dp[br0o] * value.blue.x13
				) / sums.blue.x31;
		if (sums.red.x31 != 0)
			dp[1] = (
				dp[1] * value.green.x22 +
				dp[5] * value.green.x23 +
				dp[b1o] * value.green.x12 +
				dp[br1o] * value.green.x13
				) / sums.green.x31;
		if (sums.red.x31 != 0)
			dp[2] = (
				dp[2] * value.red.x22 +
				dp[6] * value.red.x23 +
				dp[b2o] * value.red.x12 +
				dp[br2o] * value.red.x13
				) / sums.red.x31;

		// bottom and top
		for (auto dpb = UCHAR_PTR(surf.buffer + 1), dpt = UCHAR_PTR(surf.end) - tl0o, end = dpb + tdl0o,
			spb = UCHAR_PTR(data::cache_buffer + 1), spt = UCHAR_PTR(data::cache_surface.end) - tl0o;
			dpb < end; dpb += 4, dpt += 4, spb += 4, spt += 4)
		{
			if (sums.blue.x12)
				dpb[0] = (
					spb[-4] * value.blue.x21 +
					spb[0] * value.blue.x22 +
					spb[4] * value.blue.x23 +
					spb[tl0o] * value.blue.x31 +
					spb[t0o] * value.blue.x32 +
					spb[tr0o] * value.blue.x33
					) / sums.blue.x12;
			if (sums.green.x12)
				dpb[1] = (
					spb[-3] * value.green.x21 +
					spb[1] * value.green.x22 +
					spb[5] * value.green.x23 +
					spb[tl1o] * value.green.x31 +
					spb[t1o] * value.green.x32 +
					spb[tr1o] * value.green.x33
					) / sums.green.x12;
			if (sums.red.x12)
				dpb[2] = (
					spb[-2] * value.red.x21 +
					spb[2] * value.red.x22 +
					spb[6] * value.red.x23 +
					spb[tl2o] * value.red.x31 +
					spb[t2o] * value.red.x32 +
					spb[tr2o] * value.red.x33
					) / sums.red.x12;

			if (sums.blue.x32)
				dpt[0] = (
					spt[-4] * value.blue.x21 +
					spt[0] * value.blue.x22 +
					spt[4] * value.blue.x23 +
					spt[bl0o] * value.blue.x11 +
					spt[b0o] * value.blue.x12 +
					spt[br0o] * value.blue.x13
					) / sums.blue.x32;
			if (sums.green.x32)
				dpt[1] = (
					spt[-3] * value.green.x21 +
					spt[1] * value.green.x22 +
					spt[5] * value.green.x23 +
					spt[bl1o] * value.green.x11 +
					spt[b1o] * value.green.x12 +
					spt[br1o] * value.green.x13
					) / sums.green.x32;
			if (sums.red.x32)
				dpt[2] = (
					spt[-2] * value.red.x21 +
					spt[2] * value.red.x22 +
					spt[6] * value.red.x23 +
					spt[bl2o] * value.red.x11 +
					spt[b2o] * value.red.x12 +
					spt[br2o] * value.red.x13
					) / sums.red.x32;
		}

		// left and right
		for (auto dpb = UCHAR_PTR(surf.buffer + surf.size.x), dpt = dpb + tl0o, end = UCHAR_PTR(surf.end - surf.size.x),
			spb = UCHAR_PTR(data::cache_buffer + surf.size.x), spt = spb + tl0o;
			dpb < end; dpb += t0o, dpt += t0o, spb += t0o, spt += t0o)
		{
			if (sums.blue.x21)
				dpb[0] = (
					spb[0] * value.blue.x22 +
					spb[4] * value.blue.x23 +
					spb[t0o] * value.blue.x32 +
					spb[tr0o] * value.blue.x33 +
					spb[b0o] * value.blue.x12 +
					spb[br0o] * value.blue.x13
					) / sums.blue.x21;
			if (sums.green.x21)
				dpb[1] = (
					spb[1] * value.green.x22 +
					spb[5] * value.green.x23 +
					spb[t1o] * value.green.x32 +
					spb[tr1o] * value.green.x33 +
					spb[b1o] * value.green.x12 +
					spb[br1o] * value.green.x13
					) / sums.green.x21;
			if (sums.red.x21)
				dpb[2] = (
					spb[2] * value.red.x22 +
					spb[6] * value.red.x23 +
					spb[t2o] * value.red.x32 +
					spb[tr2o] * value.red.x33 +
					spb[b2o] * value.red.x12 +
					spb[br2o] * value.red.x13
					) / sums.red.x21;

			if (sums.blue.x23)
				dpb[0] = (
					spb[0] * value.blue.x22 +
					spb[4] * value.blue.x23 +
					spb[t0o] * value.blue.x32 +
					spb[tl0o] * value.blue.x31 +
					spb[b0o] * value.blue.x12 +
					spb[bl0o] * value.blue.x11
					) / sums.blue.x23;
			if (sums.green.x23)
				dpb[1] = (
					spb[1] * value.green.x22 +
					spb[5] * value.green.x23 +
					spb[t1o] * value.green.x32 +
					spb[tl1o] * value.green.x31 +
					spb[b1o] * value.green.x12 +
					spb[bl1o] * value.green.x11
					) / sums.green.x23;
			if (sums.red.x23)
				dpb[2] = (
					spb[2] * value.red.x22 +
					spb[6] * value.red.x23 +
					spb[t2o] * value.red.x32 +
					spb[tl2o] * value.red.x31 +
					spb[b2o] * value.red.x12 +
					spb[bl2o] * value.red.x11
					) / sums.red.x23;
		}

		for (auto dp = UCHAR_PTR(surf.buffer + surf.size.x + 1), end = UCHAR_PTR(surf.end - surf.size.x),
			sp = UCHAR_PTR(data::cache_buffer + surf.size.x + 1); dp < end; dp += 8, sp += 8)
		{
			for (auto x_end = dp + tdl0o; dp < x_end; dp += 4, sp += 4)
			{
				if (sums.blue.x22)
					dp[0] = (
						sp[tl0o] * value.blue.x11 + sp[t0o] * value.blue.x13 + sp[tr0o] * value.blue.x13 +
						sp[-4] * value.blue.x21 + sp[0] * value.blue.x22 + sp[4] * value.blue.x23 +
						sp[bl0o] * value.blue.x31 + sp[b0o] * value.blue.x32 + sp[br0o] * value.blue.x33
						) / sums.blue.x22;
				if (sums.green.x22)
					dp[1] = (
						sp[tl1o] * value.green.x11 + sp[t1o] * value.green.x13 + sp[tr1o] * value.green.x13 +
						sp[-3] * value.green.x21 + sp[1] * value.green.x22 + sp[5] * value.green.x23 +
						sp[bl1o] * value.green.x31 + sp[b1o] * value.green.x32 + sp[br1o] * value.green.x33
						) / sums.green.x22;
				if (sums.red.x22)
					dp[2] = (
						sp[tl2o] * value.red.x11 + sp[t2o] * value.red.x13 + sp[tr2o] * value.red.x13 +
						sp[-2] * value.red.x21 + sp[2] * value.red.x22 + sp[6] * value.red.x23 +
						sp[bl2o] * value.red.x31 + sp[b2o] * value.red.x32 + sp[br2o] * value.red.x33
						) / sums.red.x22;
			}
		}

		return SUCCESS;
	}
