const lli N = 2e5 + 5;
lli L[N], R[N], arr[N], n;

void MakeTree()
{
    stack<lli> st;
    for (int i = 1; i <= n; i++)
    {
        while (!st.empty() && arr[st.top()] < arr[i])
        {
            lli now = st.top();
            st.pop();
            L[i] = now;
        }

        if (!st.empty())
            R[st.top()] = i;

        st.push(i);
    }
}