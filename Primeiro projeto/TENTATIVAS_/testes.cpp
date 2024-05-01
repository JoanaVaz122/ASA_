#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rectangle {
    int width, height, value;
    Rectangle(int w, int h, int v) : width(w), height(h), value(v) {}
};

// Função para otimizar o corte de retângulos usando programação dinâmica
Rectangle optimize(int width, int height, vector<Rectangle>& patterns, vector<vector<int>>& memo) {
    if (width <= 0 || height <= 0) {
        return {0, 0, 0};
    }

    if (memo[width][height] != -1) {
        return {0, 0, memo[width][height]};
    }

    Rectangle rect(0, 0, 0);

    for (const auto& pattern : patterns) {
        if (width >= pattern.width && height >= pattern.height) {
            Rectangle subRect = optimize(width - pattern.width, height, patterns, memo);
            int subValue = subRect.value + pattern.value;

            if (subValue > rect.value) {
                rect = {subRect.width + pattern.width, subRect.height, subValue};
            }

            subRect = optimize(width, height - pattern.height, patterns, memo);
            subValue = subRect.value + pattern.value;

            if (subValue > rect.value) {
                rect = {subRect.width, subRect.height + pattern.height, subValue};
            }
        }
    }

    memo[width][height] = rect.value;
    return rect;
}

int main() {
    int totalWidth, totalHeight;
    cin >> totalWidth >> totalHeight;

    int n;
    cin >> n;

    vector<Rectangle> patterns;
    for (int i = 0; i < n; ++i) {
        int ai, bi, pi;
        cin >> ai >> bi >> pi;
        patterns.push_back(Rectangle(ai, bi, pi));
    }

    vector<vector<int>> memo(totalWidth + 1, vector<int>(totalHeight + 1, -1));

    Rectangle result = optimize(totalWidth, totalHeight, patterns, memo);

    cout << "Valor ótimo: " << result.value << endl;

    return 0;
}
