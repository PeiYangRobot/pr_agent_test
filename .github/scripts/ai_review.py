import sys, os
from openai import OpenAI

client = OpenAI(
    base_url="https://antigravity-manager-api.ofahxztfgt.workers.dev",
    api_key=os.environ["GEMINI_API_KEY"],
)

diff_file = sys.argv[1]
with open(diff_file, "r") as f:
    diff_content = f.read()

# Note: Antigravity lets you call any model via the Anthropic SDK
response = client.messages.create(
    model="claude-sonnet-4-6",
    messages=[
        {
            "role": "system",
            "content": "你是一位资深代码审查专家，请针对提供的 PR diff 找出潜在 bug、安全隐患、性能问题和违反最佳实践的地方。只针对变更部分输出简洁的 Markdown 列表，若未发现问题则回复“未发现明显问题”。"
        },
        {
            "role": "user",
            "content": f"请审查以下代码差异：\n\n{diff_content}"
        }
    ],
    temperature=0.0,                # 严谨审查建议用 0
    max_tokens=1024,
)

print(response.content[0].text)