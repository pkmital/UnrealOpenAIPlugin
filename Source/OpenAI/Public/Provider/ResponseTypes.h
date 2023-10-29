// OpenAI, Copyright LifeEXE. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonTypes.h"
#include "ResponseTypes.generated.h"

/*
    @todo: add more errors https://platform.openai.com/docs/guides/error-codes
*/
UENUM(BlueprintType)
enum class EOpenAIResponseError : uint8
{
    InvalidAPIKey = 0,
    NetworkError,
    ModelNotFound,
    Unknown
};

UENUM(BlueprintType)
enum class EOpenAIFinishReason : uint8
{
    Stop = 0,
    Length,
    Content_Filter,
    Function_Call,
    Null
};

USTRUCT(BlueprintType)
struct FOpenAIError
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString RawContent{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool WasError{false};
};

USTRUCT(BlueprintType)
struct FPermission
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Create_Engine{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Sampling{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Logprobs{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Search_Indices{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_View{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Allow_Fine_Tuning{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Organization{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Group{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Is_Blocking{};
};

USTRUCT(BlueprintType)
struct FOpenAIModel
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Owned_By{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FPermission> Permission;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Root{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Parent{};
};

USTRUCT(BlueprintType)
struct FListModelsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIModel> Data;
};

USTRUCT(BlueprintType)
struct FRetrieveModelResponse : public FOpenAIModel
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FBaseChoice
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Text{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};
};

USTRUCT(BlueprintType)
struct FLogProbs
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FString> Tokens;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<double> Token_Logprobs;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Top_Logprobs{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<int32> Text_Offset;
};

USTRUCT(BlueprintType)
struct FChoice : public FBaseChoice
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FLogProbs LogProbs;

    /**
      The reason the model stopped generating tokens.
      This will be stop if the model hit a natural stop point or a provided stop sequence,
      length if the maximum number of tokens specified in the request was reached, or
      content_filter if content was omitted due to a flag from our content filters.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Finish_Reason{};
};

USTRUCT(BlueprintType)
struct FChatChoice
{
    GENERATED_BODY()

    /**
      The index of the choice in the list of choices.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};

    /**
      A chat completion message generated by the model.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FMessage Message;

    /**
      The reason the model stopped generating tokens.
      This will be stop if the model hit a natural stop point or a provided stop sequence,
      length if the maximum number of tokens specified in the request was reached,
      content_filter if content was omitted due to a flag from our content filters,
      or function_call if the model called a function.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Finish_Reason{};
};

USTRUCT(BlueprintType)
struct FUsage
{
    GENERATED_BODY()

    /**
      Number of tokens in the prompt.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Prompt_Tokens{};

    /**
      Number of tokens in the generated completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Completion_Tokens{};

    /**
      Total number of tokens used in the request (prompt + completion).
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Total_Tokens{};
};

USTRUCT(BlueprintType)
struct FCompletionResponseBase
{
    GENERATED_BODY()

    /**
       A unique identifier for the completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    /**
       The object type, which is always "text_completion"
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    /**
       The Unix timestamp (in seconds) of when the completion was created.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    /**
       The model used for completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model{};

    /**
       The list of completion choices the model generated for the input prompt.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FChoice> Choices;
};

USTRUCT(BlueprintType)
struct FCompletionResponse : public FCompletionResponseBase
{
    GENERATED_BODY()

    /**
       Usage statistics for the completion request.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FUsage Usage;
};

USTRUCT(BlueprintType)
struct FCompletionStreamResponse : public FCompletionResponseBase
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FChatCompletionResponseBase
{
    GENERATED_BODY()

    /**
       A unique identifier for the chat completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    /**
       The object type, which is always chat.completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    /**
       The Unix timestamp (in seconds) of when the chat completion was created.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    /**
       The model used for the chat completion.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;
};

USTRUCT(BlueprintType)
struct FChatCompletionResponse : public FChatCompletionResponseBase
{
    GENERATED_BODY()
    /**
       A list of chat completion choices. Can be more than one if n is greater than 1.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FChatChoice> Choices;

    /**
       Usage statistics for the completion request.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FUsage Usage;
};

USTRUCT(BlueprintType)
struct FDelta
{
    GENERATED_BODY()

    /**
       The contents of the chunk message.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Content{};

    /**
       The name and arguments of a function that should be called, as generated by the model.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FFunctionCall Function_Call;

    /**
       The role of the author of this message.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Role;
};

USTRUCT(BlueprintType)
struct FChatStreamChoice
{
    GENERATED_BODY()

    /**
       A chat completion delta generated by streamed model responses.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FDelta Delta{};

    /**
       The reason the model stopped generating tokens.
       This will be stop if the model hit a natural stop point or a provided stop sequence,
       length if the maximum number of tokens specified in the request was reached,
       content_filter if content was omitted due to a flag from our content filters, or
       function_call if the model called a function.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Finish_Reason{};

    /**
       The index of the choice in the list of choices.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};
};

USTRUCT(BlueprintType)
struct FChatCompletionStreamResponse : public FChatCompletionResponseBase
{
    GENERATED_BODY()

    /**
       A list of chat completion choices. Can be more than one if n is greater than 1.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FChatStreamChoice> Choices;
};

USTRUCT(BlueprintType)
struct FEditResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FBaseChoice> Choices;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FUsage Usage;
};

USTRUCT(BlueprintType)
struct FImageResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FString> Data;
};

USTRUCT(BlueprintType)
struct FImageEditResponse : public FImageResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FImageVariationResponse : public FImageResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FEmbeddingsUsage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Prompt_Tokens{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Total_Tokens{};
};

USTRUCT(BlueprintType)
struct FEmbeddingsData
{
    GENERATED_BODY()

    /**
      The object type, which is always "embedding".
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    /**
      The index of the embedding in the list of embeddings.
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Index{};

    /**
      The embedding vector, which is a list of floats. The length of vector depends on the model as listed in the embedding guide:
      https://platform.openai.com/docs/guides/embeddings
    */
    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<float> Embedding;
};

USTRUCT(BlueprintType)
struct FEmbeddingsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FEmbeddingsData> Data;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FEmbeddingsUsage Usage;
};

USTRUCT(BlueprintType)
struct FAudioTranscriptionResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Text;
};

USTRUCT(BlueprintType)
struct FAudioTranslationResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Text;
};

USTRUCT(BlueprintType)
struct FOpenAIFile
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Bytes{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Created_At{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString FileName;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Purpose;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Status;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Status_Details;
};

USTRUCT(BlueprintType)
struct FListFilesResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Data;
};

USTRUCT(BlueprintType)
struct FUploadFileResponse : public FOpenAIFile
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FDeleteFileResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Deleted{};
};

USTRUCT(BlueprintType)
struct FRetrieveFileResponse : public FOpenAIFile
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FRetrieveFileContentResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Content;
};

USTRUCT(BlueprintType)
struct FOpenAIEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created_At{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Level;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Message;
};

USTRUCT(BlueprintType)
struct FHyperparams
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Batch_Size{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    float Learning_Rate_Multiplier{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 N_Epochs{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    float Prompt_Loss_Weight{};
};

USTRUCT(BlueprintType)
struct FBaseFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Created_At{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Fine_Tuned_Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FHyperparams Hyperparams;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Organization_ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Result_Files;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Status;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Validation_Files;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIFile> Training_Files;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    int32 Updated_At{};
};

USTRUCT(BlueprintType)
struct FFineTuneResponse : public FBaseFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIEvent> Events;
};

USTRUCT(BlueprintType)
struct FListFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FBaseFineTuneResponse> Data;
};

USTRUCT(BlueprintType)
struct FFineTuneEventsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FOpenAIEvent> Data;
};

USTRUCT(BlueprintType)
struct FDeleteFineTuneResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Object{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Deleted{};
};

USTRUCT(BlueprintType)
struct FModerationCategories
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Hate{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Hate_Threatening{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Self_Harm{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Sexual{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Sexual_Minors{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Violence{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Violence_Graphic{};
};

USTRUCT(BlueprintType)
struct FModerationScores
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Hate{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Hate_Threatening{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Self_Harm{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Sexual{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Sexual_Minors{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Violence{};

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    double Violence_Graphic{};
};

USTRUCT(BlueprintType)
struct FModerationResults
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FModerationCategories Categories;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FModerationScores Category_Scores;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    bool Flagged{};
};

USTRUCT(BlueprintType)
struct FModerationsResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString ID;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    FString Model;

    UPROPERTY(BlueprintReadOnly, Category = "OpenAI")
    TArray<FModerationResults> Results;
};
